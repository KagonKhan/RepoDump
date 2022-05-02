
template<class RESOURCE, typename ID>
template<typename ...Args>
inline void ResourceManager<RESOURCE, ID>::load(const ID& id, Args&& ...args)
{
	std::unique_ptr<RESOURCE> ptr = std::make_unique<RESOURCE>(RESOURCE());
	if (!ptr->loadFromFile(std::forward<Args>(args)...))
		throw std::runtime_error("[EROR] Cannot load file\n");

	m_ResourceMap.emplace(id, std::move(ptr));

}

template<class RESOURCE, typename ID>
inline RESOURCE& ResourceManager<RESOURCE, ID>::get(const ID& id) const
{
	auto result = m_ResourceMap.find(id);
	assert(result != m_ResourceMap.end());

	return *result->second;
}













template<typename IDENTIFIER>
template<typename ... Args>
void ResourceManager<sf::Music, IDENTIFIER>::load(const IDENTIFIER& id, Args&& ... args)
{
	std::unique_ptr<sf::Music> ptr(new sf::Music);
	if (!ptr->openFromFile(std::forward<Args>(args)...))
		throw std::runtime_error("[EROR] Cannot load file\n");

	m_ResourceMap.emplace(id, std::move(ptr));
}

template<typename IDENTIFIER>
sf::Music& ResourceManager<sf::Music, IDENTIFIER>::get(const IDENTIFIER& id) const
{
	auto result = m_ResourceMap.find(id);
	assert(result != m_ResourceMap.end());

	return *result->second;
}