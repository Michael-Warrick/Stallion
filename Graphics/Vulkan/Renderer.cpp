#include "Renderer.hpp"

Graphics::Vulkan::Renderer::Renderer(GLFWwindow *window)
    : m_Window(window), m_Surface(m_Instance.get(), window), m_Device(m_Instance.get(), m_Surface.get()),
      m_SwapChain(window, m_Surface.get(), m_Device.physical(), m_Device.logical()),
      m_Pipeline(m_Device.physical(), m_Device.logical(), m_SwapChain.imageFormat(), m_Device.msaaSamples()) {

    m_SwapChain.CreateFramebuffers(m_Pipeline.renderPass());
}

void Graphics::Vulkan::Renderer::DrawFrame() { m_SwapChain.Recreate(m_Pipeline.renderPass()); }
