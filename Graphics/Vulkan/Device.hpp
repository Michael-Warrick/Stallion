#pragma once

#include <iostream>
#include <set>
#include <vulkan/vulkan.hpp>

#include "Queue.hpp"
#include "SwapChain.hpp"

namespace Graphics {
class Device {
public:
    Device(const vk::Instance &instance, const vk::SurfaceKHR &surface);
    ~Device();

    [[nodiscard]] vk::PhysicalDevice physical() const;
    [[nodiscard]] vk::Device logical() const;
    [[nodiscard]] vk::SampleCountFlagBits msaaSamples() const;
    [[nodiscard]] static uint32_t
    FindMemoryType(vk::PhysicalDevice physicalDevice, uint32_t typeFilter,
                   vk::MemoryPropertyFlags properties);

private:
    void pickPhysicalDevice();
    bool isPhysicalDeviceSuitable(vk::PhysicalDevice physicalDevice);
    bool checkPhysicalDeviceExtensionSupport(vk::PhysicalDevice physicalDevice);

    [[nodiscard]] vk::SampleCountFlagBits getMaxUsableSamples() const;

    void createLogicalDevice();

    vk::Instance m_Instance;
    vk::SurfaceKHR m_Surface;
    vk::PhysicalDevice m_PhysicalDevice;
    vk::SampleCountFlagBits m_MSAASamples = vk::SampleCountFlagBits::e1;
    vk::Device m_LogicalDevice;
    vk::Queue m_GraphicsQueue;
    vk::Queue m_PresentQueue;

#ifdef __APPLE__
    const std::vector<const char *> m_PhysicalDeviceExtensions = {
        "VK_KHR_portability_subset", "VK_KHR_swapchain"};
#else
    const std::vector<const char *> m_PhysicalDeviceExtensions = {
        "VK_KHR_swapchain", "VK_EXT_host_query_reset"};
#endif

#ifdef NDEBUG
    const bool m_ValidationLayersEnabled = false;
#else
    const bool m_ValidationLayersEnabled = true;
#endif
    const std::vector<const char *> m_ValidationLayers = {
        "VK_LAYER_KHRONOS_validation"};
};
} // namespace Graphics
