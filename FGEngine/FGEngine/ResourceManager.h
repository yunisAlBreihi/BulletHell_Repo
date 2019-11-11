#pragma once

#include <map>
#include <string>

namespace FG
{
	class IResource;

	typedef std::map<std::string, IResource*> ResourceMap_t;
	class ResourceManager
	{
	public:
		void Shutdown();

		template <class T>
		T* GetResource(const std::string& id) const
		{
			auto it = resources.find(id);
			if (it == resources.end())
			{
				return nullptr;
			}
			else
			{
				return dynamic_cast<T*>(it->second);
			}
		}

		bool AddResource(const std::string& id, IResource* resource);
		bool HasResource(const std::string& id) const;

	protected:
		ResourceMap_t resources;
	};
}
