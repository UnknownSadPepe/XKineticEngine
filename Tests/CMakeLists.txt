# Initialize tests options.
option(XKWINDOW_TEST "Build window test application" ON)
option(XKVULKAN_TEST "Build Vulkan test application" ON)
option(XKDIRECTX12_TEST "Build DirectX12 test application" ON)

# Add XKWindowTest subdirectory.
if(XKWINDOW_TEST)
  add_subdirectory(WindowTest)
endif()

# Add XKVulkanTests subdirectory.
if(XKVULKAN_TEST)
  add_subdirectory(VulkanTest)
endif()

# Add XKDirectX12Tests subdirectory.
if(WIN32)
	if(XKDIRECTX12_TEST)
		add_subdirectory(DirectX12Test)
	endif()
endif()
