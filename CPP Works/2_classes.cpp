#include <iostream>
//#define LOG(x) std::cout << x << std::endl

// access modifier in classes is private as default
class Player {
public:
	int x, y;
	int speed;

	void Move(int xa, int ya) { //Method: functions in classes
		x += xa * speed;
		y += ya * speed;
	}
};

//struct'larda default olarak public tanýmlýdýr. Struct C'den gelir.
struct Vec2 {
	float x, y;

	void Add(const Vec2& other) {
		x += other.x;
		y += other.y;

	}

};

class Log {
public:
	const int LogLevelError = 0;
	const int LogLevelWarning = 1;
	const int LogLevelInfo = 2;
private:
	int m_LogLevel = LogLevelInfo;
public:
	void SetLevel(int level) {
		m_LogLevel = level;
	}
	void Error(const char* message) {
		if(m_LogLevel >= LogLevelError)
			std::cout << "[ERROR]: " << message << std::endl;
	}
	void Warn(const char* message) {
		if (m_LogLevel >= LogLevelWarning)
			std::cout << "[WARNING]: " << message << std::endl;
	}
	void Info(const char* message) {
		if (m_LogLevel >= LogLevelInfo)
			std::cout << "[INFO]: " << message << std::endl;
	}
};
/*
struct Entity {
	static int x, y;
	static void Print() {
		std::cout << x << ", " << y << std::endl;
	}
};
*/
/* Static olarak tanýmlanýrsa diðerlerinden girdi alamaz ?
static void Print(Entity e) {
	std::cout << e.x << ", " << e.y << std::endl;
}
*/

/*
int Entity::x; //Entity struct'ý içindeki static tanýmlama yüzünden main fonksiyona baðlamak gerekiyor, external link error
int Entity::y;
*/

//ENUMS in CPP
enum Example : unsigned char{
	A=5,B,C
};

//Constructors in CPP and Destructors in CPP
class Entity {
public:
	float X, Y;
	//constructor metotlar özel metotlardýr, aþaðýdaki gibi tanýmlanýr, birden fazla tanýmlanabilir.
	Entity() {
		X = 0.0f;
		Y = 0.0f;
		std::cout << "Created Entity!" << std::endl;
	}

	/*Entity(float x, float y) {

		X = x;
		Y = y;
	}*/

	~Entity() {//Destructor
		std::cout << "Destroyed Entity!" << std::endl;
	}

	void Print() {
		std::cout << X << ", " << Y << std::endl;
	}
};

void Function() {
	Entity e;
	e.Print();
}

int main() {

	/*Log log;
	//log.SetLevel(log.LogLevelWarning);
	//log.SetLevel(log.LogLevelError);
	log.Warn("Hello!");
	log.Error("Hello!");
	log.Info("Hello!");
	std::cin.get();*/

	/*
	Entity e;
	e.x = 2;
	e.y = 3;
	
	Entity e1;
	e1.x = 5;
	e1.y = 8;

	e.Print();
	e1.Print();
	*/
	
	Entity e;
	Function();
	e.~Entity();
	std::cin.get();
}
