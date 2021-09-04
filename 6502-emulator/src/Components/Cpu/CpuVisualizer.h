#pragma once

#include <unordered_map>
#include "Components/Cpu/Cpu.h"

class CpuVisualizer
{
private:
	std::unordered_map<uint8_t, const char*> mInstructionNames;
public:
	CpuVisualizer();
	void Visualize(Cpu* cpu);
};