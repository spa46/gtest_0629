#include <stdio.h>

class User {
private:
	virtual void foo() {}
};

class TestUser : public User {
public:
	void foo() override {
		User::foo();
	}
};

int main() {

}
