#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <memory>
#include <any>
using namespace std;

template<class T>
class IocContainer
{
public:
    using FuncType = std::function<T*()>;

     // Register a type corresponding to a key
    template<class ClassType>
    void registerType(string key)
    {
        FuncType func = [] {return new ClassType(); };
        registerType(key, func);
    }

     // Query the corresponding constructor according to the unique flag Create object
    T* resolve(string key)
    {
        if (m_map.find(key) == m_map.end())
        {
            return nullptr;
        }
        auto func = m_map[key];
        return func();
    }
    std::shared_ptr<T> resolveShared(string key)
    {
        if (m_map.find(key) == m_map.end())
        {
            return nullptr;
        }
        auto func = m_map[key];
        return std::shared_ptr<T>(func());
    }

private:
    void registerType(string key, FuncType type)
    {
        if (m_map.find(key) != m_map.end())
        {
            throw std::invalid_argument("this key has exist");
        }
        m_map.emplace(key, type);
    }

private:
    std::map<string, FuncType> m_map;
};

struct ICar
{
    virtual ~ICar() {}
    virtual void test() const = 0;
};

struct Car : ICar
{
    void test() const
    {
        cout << "Car test" << endl;
    }
};

struct Bus : ICar
{
    void test() const
    {
        cout << "Bus test" << endl;
    }
};

int main(int ac, char **av)
{
    IocContainer<ICar> ioc;
    ioc.registerType<Bus>("bus");
    ioc.registerType<Car>("car");

    std::shared_ptr<ICar> bus = ioc.resolveShared("bus");
    bus->test();

    return 0;
}
