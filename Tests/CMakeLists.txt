option(XKWINDOW_TEST "Build window test application" ON)
option(XKVULKAN_TEST "Build Vulkan test application" ON)
option(XKD3D12_TEST "Build D3D12 test application" ON)

if(XKWINDOW_TEST)
  add_subdirectory(WindowTest)
endif()

if(XKVULKAN_TEST)
  add_subdirectory(VulkanTest)
endif()

if(WIN32)
	if(XKDIRECTX12_TEST)
		add_subdirectory(D3D12Test)
	endif()
endif()
