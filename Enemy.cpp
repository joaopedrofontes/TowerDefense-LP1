#include "Enemy.h"
#include <cmath>
#include <iostream>

//Inicializar variáveis
void Enemy::initVariables()
{
	this->pointCount = rand() % 2 + 3; 
	 this->type = 0;
	 this->speed = static_cast<float>(this->pointCount) / 6;
	 this->hpMax=static_cast<int>(this->pointCount);
	 this->hp= this->hpMax;
	 this->damage= this->pointCount;
	 this->points= this->pointCount;
	 this->attackCooldownMax = 100.f;
	 this->attackCooldown = 0.f;
}

//Construtor
Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();

	if(!this->texture.loadFromFile("Textures/enemy.png")) {
		std::cout << "ERROR::ENEMY::INITTEXTURE::Could not load texture file"<<std::endl;
	}

	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(pos_x, pos_y);
	this->sprite.setScale(0.1f, 0.1f);
}

Enemy::~Enemy()
{
}

//Retornar limites
const sf::FloatRect Enemy::getBounds() const
{
	return this->sprite.getGlobalBounds();
}
//Retornar pontos
const int& Enemy::getPoints() const
{
	return this->points;
}
//Retornar dano
const int& Enemy::getDamage() const
{
	return this->damage;
}
//Retornar posição
sf::Vector2f Enemy::getPosition() const
{
    return this->sprite.getPosition();
}
//Verificar se pode atacar
const bool Enemy::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax) {

		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

//Função de atualização
void Enemy::update(const sf::Vector2f& center)
{
	// Posição atual do inimigo
    sf::Vector2f currentPosition = this->sprite.getPosition();
    
    // Calcular a direção para o centro da tela
    sf::Vector2f direction = center - currentPosition;
    
    // Calcular a magnitude da direção
	//VGA sendo aplicado
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    
    // Normalizar a direção
    if (length != 0) {
        direction /= length;
    }
    
    // Mover o inimigo na direção do centro
    this->sprite.move(direction * speed);

	updateAttack();

}
//atualizar o ataque
void Enemy::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax) {
		this->attackCooldown += 0.5f;
	}
}
//renderização
void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
		
}