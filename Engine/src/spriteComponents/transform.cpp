#include "stransform.h"
#include <physicalComponents/sprite.h>

//Contructor

s2d::Transform::Transform()
{
	this->init();
}

s2d::Transform::Transform(s2d::Sprite* attached)
{
	this->init();
	this->m_attached_sprite = attached;
}

void s2d::Transform::init()
{
	this->base_component = true;
	this->position_changed = false;
	this->m_attached_sprite = nullptr;
}

// Private functions

void s2d::Transform::setLastPosition()
{
	if (this->nextPos != this->position)
	{
		this->lastPos = this->nextPos;
		this->nextPos = this->position;
		this->position_changed = true;
	}
	else
	{
		this->position_changed = false;
	}
}

void s2d::Transform::updateTransformPosition()
{
	//Setting it centered 
	float x = 960 + this->position.x - this->textureSize.x / 2;
	float y = 540 - this->position.y - this->textureSize.y / 2;
	this->m_attached_sprite->getSprite().setPosition(sf::Vector2f(x, y));

	this->setLastPosition();
}

void s2d::Transform::setTextureSize(const s2d::Vector2& scale)
{
	s2d::Vector2 multiply = scale;

	if (multiply.x < 0)
	{
		multiply.x = multiply.x * -1;
	}
	if (multiply.y < 0)
	{
		multiply.y = multiply.y * -1;
	}

	sf::IntRect textureRect = this->m_attached_sprite->getSprite().getTextureRect();
	this->textureSize = s2d::Vector2(textureRect.width * multiply.x, textureRect.height * multiply.y);
}

void s2d::Transform::calculateScaleXByWorldPosition(const float posX)
{
	float scaleX = posX / this->textureSize.x;

	this->setScale(s2d::Vector2(scaleX, this->m_scale.y));
}

s2d::Vector2 s2d::Transform::getDefaultTextureSize() const
{
	s2d::Vector2 scale = this->m_scale;

	if (this->m_scale.x < 0)
	{
		scale.x = scale.x * -1;
	}
	if (this->m_scale.y < 0)
	{
		scale.y = scale.y * -1;
	}
	return s2d::Vector2(this->textureSize.x / scale.x, this->textureSize.y / scale.y);
}

// Public functions

void s2d::Transform::setScale(const s2d::Vector2& scale, bool b)
{
	if (this->m_scale == scale && !b)
	{
		return;
	}

	this->setTextureSize(scale);
	sf::IntRect textureRect = this->m_attached_sprite->getSprite().getTextureRect();

	this->m_scale = scale;
	this->m_attached_sprite->getSprite().setOrigin(100, 71);
	this->m_attached_sprite->getSprite().setScale(scale.x, scale.y);

	if (scale.x < 0 && scale.y < 0)
	{
		this->m_attached_sprite->getSprite().setOrigin((float)textureRect.width, (float)textureRect.height);
	}
	else if (scale.x < 0)
	{
		this->m_attached_sprite->getSprite().setOrigin((float)textureRect.width, 0);
	}
	else if (scale.y < 0)
	{
		this->m_attached_sprite->getSprite().setOrigin(0, (float)textureRect.height);
	}
	else
	{
		this->m_attached_sprite->getSprite().setOrigin(0, 0);
	}
}

void s2d::Transform::reset()
{
	this->lastPos = s2d::Vector2(0, 0);
	this->position = s2d::Vector2(0, 0);
	this->setScale(s2d::Vector2(1, 1));
}

//Public static functions

void s2d::Transform::onPositionChange(s2d::Sprite* sprite)
{
	ChildSystem::updatePositionToParent(sprite);
	ChildSystem::updateChildPositionRecursivly(sprite);
	ChildSystem::updateChildPositionToParentRecursivly(sprite);
}
