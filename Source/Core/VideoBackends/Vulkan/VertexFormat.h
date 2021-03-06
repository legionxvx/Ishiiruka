// Copyright 2016 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <array>

#include "VideoBackends/Vulkan/Constants.h"
#include "VideoCommon/NativeVertexFormat.h"

namespace Vulkan
{
class VertexFormat : public ::NativeVertexFormat
{
public:
	VertexFormat(const PortableVertexDeclaration& in_vtx_decl);
	
	// Creates or obtains a pointer to a VertexFormat representing decl.
	// If this results in a VertexFormat being created, if the game later uses a matching vertex
	// declaration, the one that was previously created will be used.
	static VertexFormat* GetOrCreateMatchingFormat(const PortableVertexDeclaration& decl);

	// Passed to pipeline state creation
	const VkPipelineVertexInputStateCreateInfo& GetVertexInputStateInfo() const
	{
		return m_input_state_info;
	}

	// Converting PortableVertexDeclaration -> Vulkan types
	void MapAttributes();
	void SetupInputState();

	// Not used in the Vulkan backend.
	void SetupVertexPointers() override;

private:
	void AddAttribute(uint32_t location, uint32_t binding, VkFormat format, uint32_t offset);

	VkVertexInputBindingDescription m_binding_description = {};

	std::array<VkVertexInputAttributeDescription, MAX_VERTEX_ATTRIBUTES> m_attribute_descriptions =
	{};

	VkPipelineVertexInputStateCreateInfo m_input_state_info = {};

	uint32_t m_num_attributes = 0;
};
}
