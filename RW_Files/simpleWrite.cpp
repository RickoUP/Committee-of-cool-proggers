#include <iostream>
#include <fstream>

int main() {

	std::ofstream out("output.txt", std::ios_base::app);
	/*
	"app" для дополнения в конец файла. По умолчанию старые данные в файле 
	затираются, "app" это предотвращает. Другие аргументы, которые можно
	передать в качестве параметра:
	"ate", "trunc", "binary", so on...

	Больше инфы здесь:
	https://www.w3schools.com/cpp/ref_fstream_ofstream.asp
	http://cppstudio.com/post/446/
	*/

	if (!out) {
		return -100;
	}

	out << "BlaBla\n";

	out << std::hex << 12131415; 
	// hex - для представления информации в 16-ричной СС. 

	out.close();
}
