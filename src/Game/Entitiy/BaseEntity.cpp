#include "BaseEntity.h"

Game::BaseEntity::BaseEntity(Utils::Vector2D pos, float deg) {
    spy = false;
    m_spy = nullptr;
    baseEntities.resize(7);

    std::vector<Utils::Vector2D> hitboxSizeList{{32, 32},
                                                {64, 64},
                                                {64, 64},
                                                {64, 64},
                                                {64, 64},
                                                {64, 64},
                                                {64, 64}};
    std::vector<std::string> baseExpoIMG{"kern", "canon_L", "canon_L_Up", "canon_L_Down", "canon_R", "canon_R_Up",
                                         "canon_R_Down"};
    std::vector<std::string> baseIMG{"kern", "canon_L_norm", "canon_L_Up_norm", "canon_L_Down_norm", "canon_R_norm",
                                     "canon_R_Up_norm", "canon_R_Down_norm"};
    std::vector<Utils::Vector2D> hitboxPosList{{0,   0},
                                               {0,   0},
                                               {14,  -16},
                                               {14,  16},
                                               {0,   0},
                                               {-14, -16},
                                               {-14, 16}};
    std::vector<Utils::Vector2D> posOffsetList{{0,    0},
                                               {-112, 0},
                                               {-62,  -80},
                                               {-62,  80},
                                               {112,  0},
                                               {62,   -80},
                                               {62,   80}};
    std::vector<float> viewOffset{0.f, 180.f, -90.f, 90.f, 0.f, -90.f, 90.f};

    if (deg > 1.f) {
        for (size_t i = 0; i < baseExpoIMG.size(); ++i) {
            baseExpoIMG[i] += "_90";
            baseIMG[i] += "_90";
        }

        hitboxPosList = {{0,   0},
                         {0,   0},
                         {14,  16},
                         {-14, 16},
                         {0,   0},
                         {14,  -16},
                         {-14, -16}};
        posOffsetList = {{0,   0},
                         {0,   -112},
                         {80,  -62},
                         {-80, -62},
                         {0,   112},
                         {80,  62},
                         {-80, 62}};
        viewOffset = {0.f, -90.f, 0.f, 180.f, 90.f, 0.f, 180.f};
    }

    for (size_t i = 0; i < baseIMG.size(); ++i) {
        auto img = std::make_shared<Drawing::Texture>(baseIMG[i], 0.f, true, "spritesheet.png");

        baseEntities[i] = new Entity(pos + posOffsetList[i], 0.f, img, hitboxPosList[i], hitboxSizeList[i],
                                     EntityType::Base, baseIMG[i].find("kern") != std::string::npos ? 1500 : 200);

        if (baseIMG[i].compare("kern") != std::string::npos) {
            if (Utils::PlayOptions::maxSpy > 0) {
                std::shared_ptr<Drawing::Texture> img = std::make_shared<Drawing::Texture>("spy", 0.f, true,
                                                                                           "spritesheet.png");
                m_spy = new Entity((pos + posOffsetList[i]), 0.f, img, EntityType::Moving, 600);
                m_spy->setBehavior(new SpyBehavior());
                spy = true;
                Utils::PlayOptions::maxSpy--;
            }

            baseEntities[i]->setBehavior(new CoreBehavior());
        } else
            baseEntities[i]->setBehavior(new CanonBehavior(baseExpoIMG[i], viewOffset[i]));
    }
}

Game::BaseEntity::~BaseEntity() {
    if (m_spy) {
        Utils::PlayOptions::maxSpy++;
        delete m_spy;
        m_spy = nullptr;
    }

    // Clean up the entities
    for (Entity *entity: baseEntities) {
        delete entity;
        entity = nullptr;
    }
    baseEntities.clear();
}

bool Game::BaseEntity::isActive() {
    bool isActive = false;
    for (int i = 1; i < baseEntities.size(); i++) {
        if (baseEntities[i]->isActive() && !baseEntities[i]->isTriggerAnimation()) {
            isActive = true;
            break;
        }
    }

    if (!isActive)
        baseEntities[0]->setTriggerAnimation(true);

    return baseEntities[0]->isActive();
}

void Game::BaseEntity::update(float deltaTime) {
    if (m_spy) {
        if (m_spy->isActive())
            m_spy->update(deltaTime);
        else {
            Utils::PlayOptions::maxSpy++;
            delete m_spy;
            m_spy = nullptr;
        }
    }

    if (!spy) {
        createSpy();
    }

    for (auto& ent : baseEntities) {
        ent->update(deltaTime);
    }
}

void Game::BaseEntity::draw(float deltaTime) {
    if (m_spy && m_spy->isActive())
        m_spy->draw(deltaTime);

    if (baseEntities[0]->isTriggerAnimation() && baseEntities[0]->isActive()) {
        baseEntities[0]->draw(deltaTime);
        return;
    }

    for (auto& ent : baseEntities) {
        ent->draw(deltaTime);
    }
}

void Game::BaseEntity::createSpy() {
    // TODO: Create Timer
    if (Utils::PlayOptions::maxSpy > 0) {
        std::shared_ptr<Drawing::Texture> img = std::make_shared<Drawing::Texture>("spy", 0.f, true, "spritesheet.png");
        m_spy = new Entity(baseEntities[0]->getOrigin(), 0.f, img, EntityType::Moving, 600);
        m_spy->setBehavior(new SpyBehavior());
        spy = true;
        Utils::PlayOptions::maxSpy--;
    }
}
