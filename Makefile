all:
	g++ -std=c++17 main.cpp -o IoCv1
test:
	chmod +x IoCv1
clean:
	$(RM) IoCv1
