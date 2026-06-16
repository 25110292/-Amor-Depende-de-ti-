#include "../include/Game.h"
#include <iostream>
#include <sstream>
#include <cmath>

std::string Game::wrapText(const std::string& text, unsigned int maxChars) const {
    std::string result;
    std::istringstream stream(text);
    std::string line, word;
    while (stream >> word) {
        if (!line.empty() && line.size() + 1 + word.size() > maxChars) {
            result += line + "\n"; line = word;
        } else { if (!line.empty()) line += " "; line += word; }
    }
    if (!line.empty()) result += line;
    return result;
}

std::string Game::replaceNames(const std::string& text) const {
    std::string result = text;
    size_t pos = 0;
    while ((pos = result.find("[NOMBRE1]", pos)) != std::string::npos) { result.replace(pos, 9, player.getName()); pos += player.getName().size(); }
    pos = 0;
    while ((pos = result.find("[NOMBRE2]", pos)) != std::string::npos) { result.replace(pos, 9, player.getLoveInterestName()); pos += player.getLoveInterestName().size(); }
    return result;
}

void Game::saveSnapshot() {
    EventSnapshot snap;
    snap.eventId = currentEventId;
    snap.totalPoints = player.getTotalPoints();
    snap.psychopathCount = player.getPsychopathCount();
    snap.eventCount = player.getEventCount();
    history.push(snap);
}

void Game::restoreLastSnapshot() {
    if (history.empty()) return;
    EventSnapshot snap = history.top(); history.pop();
    currentEventId = snap.eventId;
    player.setTotalPoints(snap.totalPoints);
    player.setPsychopathCount(snap.psychopathCount);
    player.setEventCount(snap.eventCount);
    lastLoadedImagePath = "";
    optionButtons.clear(); optionTexts.clear();
    state = GameState::PLAYING;
}

std::string Game::getEventImagePath(int eventId) const {
    std::string prefix = (player.getGender() == "M") ? "EH" : "EM";
    if (eventId == 4) return "assets/Captura_EHM4.png";
    if (eventId == 7 && player.getGender() == "F") return "assets/Captura_EH7.png";
    if (eventId == 1) return "assets/captura" + prefix + "1.png";
    return "assets/Captura_" + prefix + std::to_string(eventId) + ".png";
}

std::string Game::getFinalImagePath() const {
    std::string t = player.getRelationshipType();
    if (t == "Romantico") return "assets/Final1.png";
    if (t == "PorLastima") return "assets/Final2.png";
    return "assets/Final3.png";
}

Game::Game()
    : window(sf::VideoMode({1200u, 800u}), "Amor? Depende de ti", sf::Style::Titlebar | sf::Style::Close),
      currentEventId(1), state(GameState::COVER), previousState(GameState::COVER),
      lastLoadedImagePath(""), fadeAlpha(255.f), fadingIn(true), hoveredOption(-1), hoveredPause(0)
{
    window.setFramerateLimit(60);
    loadFont();
    if (music.openFromFile("assets/musica.ogg")) { music.setLooping(true); music.setVolume(45.f); music.play(); }
}

Game::~Game() {}

bool Game::loadFont() {
    if (font.openFromFile("assets/PlaywriteGBJ-VariableFont_wght.ttf")) return true;
    if (font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) return true;
    if (font.openFromFile("C:\\Windows\\Fonts\\segoeui.ttf")) return true;
    return false;
}

bool Game::loadImage(const std::string& path) {
    if (path == lastLoadedImagePath) return true;
    if (!backgroundTexture.loadFromFile(path)) { lastLoadedImagePath = ""; backgroundSprite.reset(); return false; }
    backgroundSprite.emplace(backgroundTexture);
    lastLoadedImagePath = path;
    return true;
}

void Game::drawRoundedRect(sf::Vector2f pos, sf::Vector2f size, sf::Color fill, sf::Color outline, float outlineThick) {
    sf::RectangleShape rect(size);
    rect.setPosition(pos);
    rect.setFillColor(fill);
    if (outlineThick > 0.f) { rect.setOutlineColor(outline); rect.setOutlineThickness(outlineThick); }
    window.draw(rect);
}

void Game::drawProgressBar() {
    drawRoundedRect({50.f, 776.f}, {1100.f, 14.f}, sf::Color(40, 30, 60));
    float pct = static_cast<float>(currentEventId - 1) / 10.f;
    drawRoundedRect({50.f, 776.f}, {1100.f * pct, 14.f}, sf::Color(200, 80, 140));
    sf::Text prog(font, "Evento " + std::to_string(currentEventId) + " de 10", 14);
    prog.setFillColor(sf::Color(200, 180, 220));
    prog.setPosition({50.f, 758.f});
    window.draw(prog);
}

void Game::drawTopBar() {
    sf::Color colPause = (hoveredPause == 1) ? sf::Color(200,60,100) : sf::Color(80,50,100,200);
    drawRoundedRect({1110.f,8.f},{80.f,34.f}, colPause, sf::Color(180,100,160), 1.5f);
    sf::Text txtPause(font, "II Pausa", 14);
    txtPause.setFillColor(sf::Color::White);
    txtPause.setPosition({1116.f,16.f});
    window.draw(txtPause);

    if (!history.empty()) {
        sf::Color colBack = (hoveredPause == 2) ? sf::Color(60,100,200) : sf::Color(50,60,100,200);
        drawRoundedRect({1020.f,8.f},{82.f,34.f}, colBack, sf::Color(100,140,220), 1.5f);
        sf::Text txtBack(font, "< Volver", 14);
        txtBack.setFillColor(sf::Color::White);
        txtBack.setPosition({1026.f,16.f});
        window.draw(txtBack);
    }
}

void Game::run() { while (window.isOpen()) { handleInput(); update(); render(); } }

void Game::update() {
    float dt = clock.restart().asSeconds();
    if (fadingIn) { fadeAlpha -= 300.f * dt; if (fadeAlpha <= 0.f) { fadeAlpha = 0.f; fadingIn = false; } }
}

void Game::handleInput() {
    while (const std::optional ev = window.pollEvent()) {
        if (ev->is<sf::Event::Closed>()) { window.close(); return; }

        if (const auto* mm = ev->getIf<sf::Event::MouseMoved>()) {
            float mx = static_cast<float>(mm->position.x);
            float my = static_cast<float>(mm->position.y);
            hoveredOption = -1;
            for (int i = 0; i < (int)optionButtons.size(); i++)
                if (optionButtons[i].getGlobalBounds().contains({mx,my})) hoveredOption = i;
            hoveredPause = 0;
            if (mx>=1110&&mx<=1190&&my>=8&&my<=42) hoveredPause=1;
            if (mx>=1020&&mx<=1102&&my>=8&&my<=42) hoveredPause=2;
        }

        if (const auto* key = ev->getIf<sf::Event::KeyPressed>()) {
            if (key->code == sf::Keyboard::Key::Escape) {
                if (state==GameState::PLAYING) { previousState=state; state=GameState::PAUSED; }
                else if (state==GameState::PAUSED) { state=GameState::PLAYING; }
                else window.close();
                return;
            }
        }

        if (state == GameState::COVER) {
            if (ev->is<sf::Event::MouseButtonPressed>() || ev->is<sf::Event::KeyPressed>())
                { fadeAlpha=255.f; fadingIn=true; state=GameState::INPUT_NAME; }
        }
        else if (state==GameState::INPUT_NAME || state==GameState::INPUT_LOVE_NAME) {
            if (const auto* txt = ev->getIf<sf::Event::TextEntered>()) {
                unsigned int c = txt->unicode;
                if (c==8 && !inputBuffer.empty()) inputBuffer.pop_back();
                else if ((c=='\r'||c=='\n') && !inputBuffer.empty()) {
                    if (state==GameState::INPUT_NAME) { player.setName(inputBuffer); inputBuffer.clear(); fadeAlpha=255.f; fadingIn=true; state=GameState::INPUT_GENDER; }
                    else { player.setLoveInterestName(inputBuffer); inputBuffer.clear(); fadeAlpha=255.f; fadingIn=true; state=GameState::PLAYING; lastLoadedImagePath=""; }
                } else if (c>=32&&c<128&&inputBuffer.size()<20) inputBuffer+=static_cast<char>(c);
            }
        }
        else if (state==GameState::INPUT_GENDER) {
            if (const auto* click = ev->getIf<sf::Event::MouseButtonPressed>()) {
                float mx=static_cast<float>(click->position.x), my=static_cast<float>(click->position.y);
                if (mx>=250&&mx<=550&&my>=320&&my<=450) { player.setGender("M"); fadeAlpha=255.f; fadingIn=true; state=GameState::INPUT_LOVE_NAME; }
                else if (mx>=650&&mx<=950&&my>=320&&my<=450) { player.setGender("F"); fadeAlpha=255.f; fadingIn=true; state=GameState::INPUT_LOVE_NAME; }
            }
        }
        else if (state==GameState::PLAYING) {
            if (const auto* click = ev->getIf<sf::Event::MouseButtonPressed>()) {
                float mx=static_cast<float>(click->position.x), my=static_cast<float>(click->position.y);
                if (mx>=1110&&mx<=1190&&my>=8&&my<=42) { previousState=state; state=GameState::PAUSED; return; }
                if (!history.empty()&&mx>=1020&&mx<=1102&&my>=8&&my<=42) { restoreLastSnapshot(); fadeAlpha=180.f; fadingIn=true; return; }
                for (size_t i=0; i<optionButtons.size(); i++) {
                    if (optionButtons[i].getGlobalBounds().contains({mx,my})) {
                        saveSnapshot();
                        const Event& cur = eventManager.getEvent(currentEventId);
                        player.addPoints(cur.options[i].points, cur.options[i].type);
                        player.incrementEventCount();
                        currentEventId++;
                        lastLoadedImagePath=""; optionButtons.clear(); optionTexts.clear();
                        fadeAlpha=200.f; fadingIn=true;
                        if (currentEventId>eventManager.getTotalEvents()) state=GameState::SHOWING_FINAL;
                        break;
                    }
                }
            }
        }
        else if (state==GameState::PAUSED) {
            if (const auto* click = ev->getIf<sf::Event::MouseButtonPressed>()) {
                float mx=static_cast<float>(click->position.x), my=static_cast<float>(click->position.y);
                if (mx>=450&&mx<=750&&my>=335&&my<=405) state=GameState::PLAYING;
                else if (mx>=450&&mx<=750&&my>=425&&my<=495) window.close();
            }
        }
        else if (state==GameState::SHOWING_FINAL) {
            if (ev->is<sf::Event::MouseButtonPressed>()) { fadeAlpha=255.f; fadingIn=true; state=GameState::SHOWING_CREDITS; }
        }
        else if (state==GameState::SHOWING_CREDITS) {
            if (ev->is<sf::Event::MouseButtonPressed>() || ev->is<sf::Event::KeyPressed>()) window.close();
        }
    }
}

void Game::render() {
    window.clear(sf::Color(15,8,28));
    switch(state) {
        case GameState::COVER:           renderCover(); break;
        case GameState::INPUT_NAME:      renderInputScreen("Ingresa tu nombre:","(max 20 caracteres, presiona Enter)"); break;
        case GameState::INPUT_GENDER:    renderGenderScreen(); break;
        case GameState::INPUT_LOVE_NAME: renderInputScreen("Nombre de tu interes romantico:","(max 20 caracteres, presiona Enter)"); break;
        case GameState::PLAYING:         displayEvent(); break;
        case GameState::PAUSED:          displayPauseMenu(); break;
        case GameState::SHOWING_FINAL:   displayFinal(); break;
        case GameState::SHOWING_CREDITS: displayCredits(); break;
    }
    if (fadeAlpha > 0.f) {
        sf::RectangleShape fadeRect({1200.f,800.f});
        fadeRect.setFillColor(sf::Color(0,0,0,static_cast<uint8_t>(fadeAlpha)));
        window.draw(fadeRect);
    }
    window.display();
}

void Game::renderCover() {
    if (loadImage("assets/COVER.png") && backgroundSprite) {
        sf::Vector2u ts = backgroundTexture.getSize();
        if (ts.x>0&&ts.y>0) { backgroundSprite->setScale({1200.f/ts.x,800.f/ts.y}); backgroundSprite->setPosition({0.f,0.f}); window.draw(*backgroundSprite); }
    }
    sf::RectangleShape grad({1200.f,220.f}); grad.setPosition({0.f,580.f}); grad.setFillColor(sf::Color(0,0,0,150)); window.draw(grad);
    sf::Text hint(font,"Haz clic para comenzar",24);
    hint.setFillColor(sf::Color(255,220,240));
    hint.setPosition({370.f,740.f});
    window.draw(hint);
}

void Game::renderInputScreen(const std::string& prompt, const std::string& subtitle) {
    for (int i=0;i<8;i++) {
        sf::RectangleShape band({1200.f,100.f}); band.setPosition({0.f,static_cast<float>(i*100)});
        band.setFillColor(sf::Color(15+i*4,8,28+i*7)); window.draw(band);
    }
    drawRoundedRect({200.f,220.f},{800.f,360.f},sf::Color(30,15,50,230),sf::Color(180,80,140),2.f);
    sf::Text gameTitle(font,"Amor? Depende de ti",38); gameTitle.setFillColor(sf::Color(255,180,210)); gameTitle.setPosition({270.f,80.f}); window.draw(gameTitle);
    drawRoundedRect({270.f,135.f},{660.f,2.f},sf::Color(200,100,160));
    sf::Text promptText(font,prompt,24); promptText.setFillColor(sf::Color::White); promptText.setPosition({280.f,270.f}); window.draw(promptText);
    if (!subtitle.empty()) { sf::Text sub(font,subtitle,15); sub.setFillColor(sf::Color(160,140,190)); sub.setPosition({280.f,308.f}); window.draw(sub); }
    drawRoundedRect({240.f,340.f},{720.f,58.f},sf::Color(20,12,40),sf::Color(200,100,160),2.f);
    sf::Text inputText(font,inputBuffer+"_",26); inputText.setFillColor(sf::Color(255,220,240)); inputText.setPosition({258.f,352.f}); window.draw(inputText);
    sf::Text enterHint(font,"Presiona Enter para continuar",14); enterHint.setFillColor(sf::Color(120,100,150)); enterHint.setPosition({380.f,418.f}); window.draw(enterHint);
}

void Game::renderGenderScreen() {
    for (int i=0;i<8;i++) {
        sf::RectangleShape band({1200.f,100.f}); band.setPosition({0.f,static_cast<float>(i*100)});
        band.setFillColor(sf::Color(15+i*4,8,28+i*7)); window.draw(band);
    }
    drawRoundedRect({200.f,180.f},{800.f,420.f},sf::Color(30,15,50,230),sf::Color(180,80,140),2.f);
    sf::Text gameTitle(font,"Amor? Depende de ti",38); gameTitle.setFillColor(sf::Color(255,180,210)); gameTitle.setPosition({270.f,80.f}); window.draw(gameTitle);
    drawRoundedRect({270.f,135.f},{660.f,2.f},sf::Color(200,100,160));
    sf::Text title(font,"Quien eres tu en esta historia?",26); title.setFillColor(sf::Color::White); title.setPosition({280.f,230.f}); window.draw(title);
    drawRoundedRect({250.f,320.f},{300.f,90.f},sf::Color(50,80,180),sf::Color(150,180,255),2.f);
    sf::Text txtH(font,"Hombre",28); txtH.setFillColor(sf::Color::White); txtH.setPosition({320.f,348.f}); window.draw(txtH);
    drawRoundedRect({650.f,320.f},{300.f,90.f},sf::Color(160,40,100),sf::Color(255,150,200),2.f);
    sf::Text txtM(font,"Mujer",28); txtM.setFillColor(sf::Color::White); txtM.setPosition({755.f,348.f}); window.draw(txtM);
}

void Game::displayEvent() {
    const Event& cur = eventManager.getEvent(currentEventId);
    if (loadImage(getEventImagePath(currentEventId)) && backgroundSprite) {
        sf::Vector2u ts=backgroundTexture.getSize();
        if (ts.x>0&&ts.y>0) { backgroundSprite->setScale({1200.f/ts.x,400.f/ts.y}); backgroundSprite->setPosition({0.f,0.f}); window.draw(*backgroundSprite); }
    } else drawRoundedRect({0.f,0.f},{1200.f,400.f},sf::Color(30,20,50));

    for (int i=0;i<6;i++) { sf::RectangleShape g({1200.f,30.f}); g.setPosition({0.f,static_cast<float>(340+i*10)}); g.setFillColor(sf::Color(0,0,0,static_cast<uint8_t>(i*35))); window.draw(g); }
    drawRoundedRect({0.f,395.f},{1200.f,405.f},sf::Color(10,5,20,240));
    drawProgressBar();
    drawTopBar();

    sf::Text titleText(font,replaceNames(cur.title),30); titleText.setPosition({50.f,406.f}); titleText.setFillColor(sf::Color(255,190,210)); window.draw(titleText);
    sf::Text descText(font,wrapText(replaceNames(cur.description),72),18); descText.setPosition({50.f,446.f}); descText.setFillColor(sf::Color(230,220,240)); window.draw(descText);
    createOptionButtons(cur);
}

void Game::createOptionButtons(const Event& evt) {
    optionButtons.clear(); optionTexts.clear();
    const int startY=560, endY=755, n=static_cast<int>(evt.options.size()), spacing=6;
    const int btnH=(endY-startY-spacing*(n-1))/n;
    int yPos=startY;
    for (int i=0;i<n;i++) {
        bool hovered=(hoveredOption==i);
        const std::string& t=evt.options[i].type;
        sf::Color base,hover;
        if      (t=="Romantico")  {base={120,25,60};  hover={180,40,90};}
        else if (t=="PorLastima") {base={25,50,130};  hover={40,80,190};}
        else if (t=="Toxico")     {base={140,65,10};  hover={200,95,20};}
        else                      {base={40,40,40};   hover={70,70,70};}
        sf::RectangleShape btn({1100.f,static_cast<float>(btnH)});
        btn.setPosition({50.f,static_cast<float>(yPos)});
        btn.setFillColor(hovered?hover:base);
        btn.setOutlineColor(hovered?sf::Color(255,200,230):sf::Color(80,60,100));
        btn.setOutlineThickness(hovered?2.f:1.f);
        optionButtons.push_back(btn);
        sf::Text optTxt(font,wrapText(replaceNames(evt.options[i].text),80),17);
        optTxt.setPosition({68.f,static_cast<float>(yPos+8)});
        optTxt.setFillColor(hovered?sf::Color::White:sf::Color(220,210,230));
        optionTexts.push_back(optTxt);
        yPos+=btnH+spacing;
    }
    for (size_t i=0;i<optionButtons.size();i++) { window.draw(optionButtons[i]); window.draw(optionTexts[i]); }
}

void Game::displayPauseMenu() {
    sf::RectangleShape overlay({1200.f,800.f}); overlay.setFillColor(sf::Color(0,0,0,200)); window.draw(overlay);
    drawRoundedRect({380.f,250.f},{440.f,300.f},sf::Color(25,12,45,245),sf::Color(200,100,160),2.f);
    sf::Text title(font,"Pausa",40); title.setFillColor(sf::Color(255,180,210)); title.setPosition({530.f,265.f}); window.draw(title);
    drawRoundedRect({380.f,318.f},{440.f,2.f},sf::Color(180,80,140));
    drawRoundedRect({450.f,335.f},{300.f,70.f},sf::Color(60,160,80),sf::Color(150,255,180),2.f);
    sf::Text cont(font,"Continuar",26); cont.setFillColor(sf::Color::White); cont.setPosition({530.f,352.f}); window.draw(cont);
    drawRoundedRect({450.f,425.f},{300.f,70.f},sf::Color(160,40,60),sf::Color(255,130,150),2.f);
    sf::Text salir(font,"Salir del juego",22); salir.setFillColor(sf::Color::White); salir.setPosition({490.f,445.f}); window.draw(salir);
    sf::Text hint(font,"[ ESC para continuar ]",14); hint.setFillColor(sf::Color(140,120,170)); hint.setPosition({490.f,510.f}); window.draw(hint);
}

void Game::displayFinal() {
    if (loadImage(getFinalImagePath()) && backgroundSprite) {
        sf::Vector2u ts=backgroundTexture.getSize();
        if (ts.x>0&&ts.y>0) { backgroundSprite->setScale({1200.f/ts.x,800.f/ts.y}); backgroundSprite->setPosition({0.f,0.f}); window.draw(*backgroundSprite); }
    }
    sf::RectangleShape overlay({1200.f,800.f}); overlay.setFillColor(sf::Color(0,0,0,165)); window.draw(overlay);
    std::string relType=player.getRelationshipType();
    sf::Color relColor=(relType=="Romantico")?sf::Color(255,150,190):(relType=="PorLastima")?sf::Color(100,180,255):(relType=="Toxico")?sf::Color(255,160,60):sf::Color(200,60,60);
    drawRoundedRect({60.f,50.f},{1080.f,680.f},sf::Color(10,5,20,200),relColor,2.f);
    sf::Text title(font,getRelationshipDescription(),34); title.setFillColor(relColor); title.setPosition({80.f,65.f}); window.draw(title);
    drawRoundedRect({80.f,118.f},{1040.f,2.f},relColor);
    sf::Text ftText(font,wrapText(replaceNames(getFinalText()),80),16); ftText.setPosition({80.f,135.f}); ftText.setFillColor(sf::Color(235,230,245)); window.draw(ftText);
    sf::Text credit(font,player.getName()+" & "+player.getLoveInterestName(),22); credit.setFillColor(relColor); credit.setPosition({480.f,670.f}); window.draw(credit);
    sf::Text hint(font,"Haz clic para ver los creditos",15); hint.setFillColor(sf::Color(150,140,170)); hint.setPosition({450.f,710.f}); window.draw(hint);
}

void Game::displayCredits() {
    for (int i=0;i<8;i++) { sf::RectangleShape band({1200.f,100.f}); band.setPosition({0.f,static_cast<float>(i*100)}); band.setFillColor(sf::Color(10+i*2,5,20+i*4)); window.draw(band); }
    sf::Text titulo(font,"Amor? Depende de ti",48); titulo.setFillColor(sf::Color(255,180,210)); titulo.setPosition({230.f,60.f}); window.draw(titulo);
    drawRoundedRect({100.f,128.f},{1000.f,2.f},sf::Color(200,100,160));
    drawRoundedRect({200.f,160.f},{800.f,500.f},sf::Color(20,10,38,230),sf::Color(180,80,140),2.f);

    auto drawCredit=[&](const std::string& label,const std::string& name,float y,sf::Color col=sf::Color(255,220,240)){
        sf::Text lbl(font,label,16); lbl.setFillColor(sf::Color(160,140,190)); lbl.setPosition({230.f,y}); window.draw(lbl);
        sf::Text nm(font,name,26); nm.setFillColor(col); nm.setPosition({230.f,y+22.f}); window.draw(nm);
    };

    drawCredit("Desarrollo y Programacion","Sofia Rodriguez",185.f,sf::Color(255,180,210));
    drawCredit("Narrativa y Diseno","Ximena Gonzalez",270.f,sf::Color(255,180,210));
    drawRoundedRect({220.f,360.f},{760.f,1.f},sf::Color(100,60,120));
    drawCredit("Motor grafico","SFML 3.0",380.f,sf::Color(180,200,255));
    drawCredit("Lenguaje","C++17",455.f,sf::Color(180,200,255));
    drawCredit("Musica","Pixabay - Royalty Free Music",530.f,sf::Color(180,200,255));

    drawRoundedRect({100.f,678.f},{1000.f,2.f},sf::Color(200,100,160));
    sf::Text gracias(font,"Gracias por jugar  <3",28); gracias.setFillColor(sf::Color(255,160,200)); gracias.setPosition({420.f,700.f}); window.draw(gracias);
    sf::Text hint(font,"Haz clic para salir",14); hint.setFillColor(sf::Color(120,100,150)); hint.setPosition({530.f,760.f}); window.draw(hint);
}

std::string Game::getRelationshipDescription() const {
    std::string t=player.getRelationshipType();
    if (t=="Romantico") return "Final Romantico -- Para siempre, en serio";
    if (t=="PorLastima") return "Final Por Lastima -- Juntos, pero distantes";
    if (t=="Toxico") return "Final Toxico -- Te quiero, a mi manera";
    return "Final Psicopata -- El amor no necesita permiso";
}

std::string Game::getFinalText() const {
    std::string t=player.getRelationshipType();
    if (t=="Romantico") return "Se casan en una pequena ceremonia con sus amigos de la uni. [NOMBRE2] llora en el altar -- tu tambien, pero lo niegas. Anos despues tienen dos hijos que heredan el caos de sus padres. En las noches, cuando todo esta en silencio, [NOMBRE2] te dice: 'te acuerdas que todo empezo porque ibas corriendo?' Tu sonries. Claro que te acuerdas.";
    if (t=="PorLastima") return "Se casan. La boda esta bien, la vida tambien. Pero con los anos cada uno fue construyendo su propio mundo aparte. [NOMBRE1] tiene a 'alguien con quien platicar en el trabajo'. [NOMBRE2] tambien. Ninguno pregunta, ninguno responde. No hay drama -- hay algo peor: comodidad sin conexion. Siguen juntos porque asi es mas facil que empezar de cero.";
    if (t=="Toxico") return "La relacion dura, de milagro. Hay momentos buenos -- pocos -- y momentos donde [NOMBRE2] llora en el bano y [NOMBRE1] ni se da cuenta. Se separan, regresan, se vuelven a separar. Al final uno de los dos manda el mensaje de 'necesito espacio' un jueves por la noche. El otro lo lee, suspira, y pone like a una foto de Instagram. Fin.";
    return "[NOMBRE2] no recuerda exactamente como llego a este punto, pero aqui esta. [NOMBRE1] tiene contrasenas, ubicacion en tiempo real y un album de fotos organizado por fecha. 'Es que te quiero mucho', dice. [NOMBRE2] asiente. Afuera llueve. Esta historia no tiene final feliz -- tiene final inevitable. Creditos en rojo.";
}
