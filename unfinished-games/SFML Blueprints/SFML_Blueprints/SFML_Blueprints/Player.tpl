template<typename ... Args>
void Player::setPosition(Args&& ... args)
{
	m_Ship.setPosition(std::forward<Args>(args)...);
}