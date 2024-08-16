#pragma once
#include <chrono>
#include <iostream>


struct TimeTaken
{
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> end;

	std::chrono::duration<float> duration;

	const char* m_info;

	TimeTaken(const char* info) : m_info(info), duration(0.0f)
	{
		start = std::chrono::high_resolution_clock::now();
	}

	~TimeTaken()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		float duration_ms = duration.count() * 1000.0f;
		std::cout << m_info << " - time took: " << duration_ms << "ms \n";
	}
};