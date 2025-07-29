-- ~/premake5.lua

workspace "Alisa"
	architecture "x86_64"
	startproject "HelloAlisa"
	
	configurations
	{
		"Debug",
		"Release",
	}
	
	flags
	{
		"MultiProcessorCompile",	
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Core"
	include "Alisa"
group ""

group "Misc"
	include "Samples/HelloAlisa"
group ""