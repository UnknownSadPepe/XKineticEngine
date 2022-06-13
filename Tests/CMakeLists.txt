# Initialize tests options.
option(BUILD_WINDOW_TEST "Build window test application" ON)
option(BUILD_VULKAN_TEST "Build Vulkan test application" ON)
option(BUILD_DIRECTX12_TEST "Build DirectX12 test application" ON)

# Add XKWindowTest subdirectory.
if(BUILD_WINDOW_TEST)
  add_subdirectory(WindowTest)
endif()

# Add XKVulkanTests subdirectory.
if(BUILD_VULKAN_TEST)
  add_subdirectory(VulkanTest)
endif()

# Add XKDirectX12Tests subdirectory.
if(WIN32)
	if(BUILD_DIRECTX12_TEST)
		add_subdirectory(DirectX12Test)
	endif()
endif()
