#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/Memory.h"
#include "Core/Time.h"
#include "Renderer/Render.h"
#include <iostream>
#include <chrono>

using namespace std;


//ctrl +k +c = ez comment

int main(int argc, char* argv[]) {

	kiko::Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("CSC196", 800, 600);

	while (true) {
		//renderer.SetColor(255, 0, 0, 255);
		renderer.BeginFrame();
		//draw
		renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), kiko::random(256));
		renderer.DrawPoint(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()));
		//renderer.DrawLine();
		renderer.EndFrame();
	}

	/*kiko::g_memoryTracker.DisplayInfo();
	int* p = new int;
	kiko::g_memoryTracker.DisplayInfo();
	delete p;
	kiko::g_memoryTracker.DisplayInfo();

	kiko::Time timer;
	for (int i = 0; i < 1000000; i++) {}
	cout << timer.GetElapsedSeconds() << endl;*/

	/*auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000000000; i++) {}
	auto end = std::chrono::high_resolution_clock::now();

	cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << endl;*/

	/*for (int i = 0; i < 10; i++) {
		int* p = new int;
		delete p;
	}

	cout << kiko::getFilePath() << endl;
	kiko::setFilePath("../../../Build/Assets");
	cout << kiko::getFilePath() << endl;
	size_t size;
	kiko::getFileSize("game.txt", size);
	cout << size << endl;

	std::string s;
	kiko::readFile("game.txt", s);
	cout << s << endl;

	kiko::seedRandom((unsigned int)time(nullptr));
	for (int i = 0; i < 10; i++) {
		cout << kiko::random(20) + 1 << endl;
	}*/

}

