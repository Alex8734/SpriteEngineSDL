#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <calculationComponents/vector2.h>
#include <UIToolButtonsModels.h>

namespace s2d
{
    class Sprite;
    class SpriteRepository
    {
    private:
        std::vector<s2d::Sprite*> m_sprites;

        size_t getIndexAtName(const std::string& name) const;
        void addChildsToDelete(std::vector<s2d::Sprite*>& childs, s2d::Sprite* parent);
        void eraseWithId(uint8_t id);

    public:
        s2d::Sprite* child_to_parent;
        s2d::Sprite* right_clicked_sprite;
        s2d::Sprite* sprite_in_inspector; 
        s2d::Sprite* sprited_hovered_in_hierarchy;

        s2d::EditorTools current_tool;

        SpriteRepository();
        ~SpriteRepository();
    
        size_t amount() const { return this->m_sprites.size(); }
        s2d::Sprite* const readAt(size_t idx);
        const s2d::Sprite* const readAt(size_t idx, bool constConst) const;
        void deleteAt(size_t idx);
        void deleteWithName(const std::string& name);
        void add(s2d::Sprite* ref);
        s2d::Sprite* getSpriteWithName(const std::string& name);
    };
}

