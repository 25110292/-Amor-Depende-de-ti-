#include "../include/EventManager.h"

EventManager::EventManager() {
    loadEvents();
}

void EventManager::loadEvents() {

    // Evento 1 - Choque de apuntes
    Event e1;
    e1.id = 1;
    e1.title = "Choque de apuntes";
    e1.description = "Primer dia de clases. Vas corriendo al salon y chocas con [NOMBRE2], tirando todos sus apuntes. Que haces?";
    e1.imagePath = "assets/event1.png";
    e1.options = {
        {"Te ayudas a recoger todo, te disculpas con una sonrisa y ofreces copiarle los apuntes que se mancharon.", 3, "Romantico"},
        {"Lo recoges todo torpemente, tartamudeas una disculpa y te vas rojo/a de verguenza sin decir mas.", 2, "PorLastima"},
        {"Le dices 'oye, tu tambien ibas corriendo' y sigues de largo.", 1, "Toxico"}
    };
    events.push_back(e1);

    // Evento 2 - Proyecto en equipo
    Event e2;
    e2.id = 2;
    e2.title = "Proyecto en equipo";
    e2.description = "El profesor asigna proyectos en equipo al azar. Te toca con [NOMBRE2]. Te manda mensaje para coordinarse. Que respondes?";
    e2.imagePath = "assets/event2.png";
    e2.options = {
        {"Propones un cafe para planear juntos, dices que tienes ideas y preguntas cuales son las suyas primero.", 3, "Romantico"},
        {"Dices 'si claro' y esperas a que [NOMBRE2] organice todo porque no quieres estorbar.", 2, "PorLastima"},
        {"Le dices que ya investigaste todo, armaste el 80% y que solo necesitas que firme. 'Es por su bien.'", 0, "Psicopata"}
    };
    events.push_back(e2);

    // Evento 3 - La cafeteria
    Event e3;
    e3.id = 3;
    e3.title = "La cafeteria";
    e3.description = "Hora del almuerzo. Ves a [NOMBRE2] sentado/a solo/a con cara de estres, mirando su celular. Te acercas?";
    e3.imagePath = "assets/event3.png";
    e3.options = {
        {"Te sientas al lado y preguntas 'todo bien? Traigo extra de papas si eso ayuda.' Con una sonrisa.", 3, "Romantico"},
        {"Te quedas de pie un rato sin saber si sentarte, al final te vas porque 'no quieres incomodar'.", 2, "PorLastima"},
        {"Te sientas sin preguntar y empiezas a hablar de ti mismo/a sin notar que esta mal.", 1, "Toxico"}
    };
    events.push_back(e3);

    // Evento 4 - La fiesta del viernes
    Event e4;
    e4.id = 4;
    e4.title = "La fiesta del viernes";
    e4.description = "Un companero hace fiesta. [NOMBRE2] tambien va. En algun momento estan los dos solos en la terraza. Que haces?";
    e4.imagePath = "assets/event4.png";
    e4.options = {
        {"Aprovechas para platicar de verdad -- gustos, suenos, miedos. Al final dices 'me alegra que coincidamos aqui'.", 3, "Romantico"},
        {"Te pones intenso/a, dices que llevas semanas 'estudiandole' y que 'sientes que hay algo especial'. Lo acorrala un poco.", 1, "Toxico"},
        {"Le muestras el album de fotos que lleva semanas guardando de [NOMBRE2] en su celular. 'Solo por si acaso.'", 0, "Psicopata"}
    };
    events.push_back(e4);

    // Evento 5 - El examen perdido
    Event e5;
    e5.id = 5;
    e5.title = "El examen perdido";
    e5.description = "[NOMBRE2] te llama desesperado/a -- reprobo un parcial y esta al borde del llanto. Son las 11pm. Que haces?";
    e5.imagePath = "assets/event5.png";
    e5.options = {
        {"Le dices 'vente, armamos un plan de rescate con cafe y apuntes'. Te quedas hasta la madrugada ayudando.", 3, "Romantico"},
        {"Lo escuchas una hora por telefono sin saber que decir, solo dices 'ay no' cada vez que puedes.", 2, "PorLastima"},
        {"Le dices 'ya te lo dije, debiste estudiar mas' y le mandas un meme de 'esto es lo que pasa'.", 1, "Toxico"}
    };
    events.push_back(e5);

    // Evento 6 - Los celos
    Event e6;
    e6.id = 6;
    e6.title = "Los celos";
    e6.description = "Ves a [NOMBRE2] riendo con otra persona en el pasillo. Se ven muy comodos. Algo en ti se mueve raro. Que haces?";
    e6.imagePath = "assets/event6.png";
    e6.options = {
        {"Respiras. Luego buscas a [NOMBRE2] y le dices honestamente 'oye, creo que me gustas' para aclarar el asunto.", 3, "Romantico"},
        {"Te vas a tu cuarto, escuchas musica triste y aceptas que 'nunca ibas a tener oportunidad de todas formas'.", 2, "PorLastima"},
        {"Investigas quien es esa persona, le mandas mensaje desde cuenta falsa diciendole que se aleje. Solo precaucion.", 0, "Psicopata"}
    };
    events.push_back(e6);

    // Evento 7 - La confesion
    Event e7;
    e7.id = 7;
    e7.title = "La confesion";
    e7.description = "[NOMBRE2] te busca nervioso/a y te dice 'creo que me gustas'. Te mira esperando respuesta. Silencio. Que dices?";
    e7.imagePath = "assets/event7.png";
    e7.options = {
        {"Sonries, dices 'yo tambien llevo un rato con eso rondando' y propones una primera cita para esa misma tarde.", 3, "Romantico"},
        {"Dices 'ay... no se si merezco a alguien tan bueno/a como tu' y lo dejas con cara de signo de interrogacion.", 2, "PorLastima"},
        {"Dices 'depende, que tan en serio lo dices?' y empiezas a poner condiciones antes de responder nada.", 1, "Toxico"}
    };
    events.push_back(e7);

    // Evento 8 - Cita final
    Event e8;
    e8.id = 8;
    e8.title = "Cita final";
    e8.description = "Primera cita. Todo va bien hasta que a [NOMBRE2] se le derrama el refresco encima. Se pone rojo/a de verguenza. Como termina la noche?";
    e8.imagePath = "assets/event8.png";
    e8.options = {
        {"Te ries con el/ella, dices 'ahora somos el chisme de la semana' y pides otra bebida para brindar 'por los desastres bonitos'.", 3, "Romantico"},
        {"Le dices 'no te preocupes, a mi siempre me pasan cosas peores' y listas 5 anecdotas tuyas para hacerlo/a sentir menos mal.", 2, "PorLastima"},
        {"Sacas un kit de emergencia de tu mochila que incluye ropa de su talla que 'por casualidad' traias. Lo miras fijamente.", 0, "Psicopata"}
    };
    events.push_back(e8);

    // Evento 9 - La graduacion
    Event e9;
    e9.id = 9;
    e9.title = "La graduacion  (4 anos despues)";
    e9.description = "Por fin llego el dia. Los dos se graduan juntos. [NOMBRE2] te busca entre la multitud, diploma en mano y ojos brillosos. Sus familias los estan mirando. Como vives este momento?";
    e9.imagePath = "assets/event9.png";
    e9.options = {
        {"Lo/la abrazas fuerte, le dices al oido 'esto es solo el principio' y propones celebrar solos despues.", 3, "Romantico"},
        {"Le dices 'lo logramos' con voz entrecortada, te emocionas tanto que terminas llorando tu mas que el/ella.", 2, "PorLastima"},
        {"Aprovechas para recordarle que tu sacaste mejor promedio y que 'sin tus apuntes no habria llegado'. Lo dices en serio.", 1, "Toxico"}
    };
    events.push_back(e9);

    // Evento 10 - La propuesta
    Event e10;
    e10.id = 10;
    e10.title = "La propuesta  (2 anos mas tarde)";
    e10.description = "Han pasado 6 anos desde aquel choque de apuntes. Hoy es un martes cualquiera. [NOMBRE2] te mira fijo/a y dice: 'Te imaginas que esto fuera para siempre?' Que haces?";
    e10.imagePath = "assets/event10.png";
    e10.options = {
        {"Sacas el anillo que llevas semanas cargando 'esperando el momento perfecto'. Resulta que un martes cualquiera era el momento perfecto.", 3, "Romantico"},
        {"Dices 'y si no soy suficiente para tanto tiempo?' Le dejas la carga emocional a el/ella de convencerte. Lo hace. Como siempre.", 2, "PorLastima"},
        {"Sacas una carpeta con el contrato prenupcial, el plan de vida a 30 anos y el nombre del primer hijo. Ya tiene nombre.", 0, "Psicopata"}
    };
    events.push_back(e10);
}

const Event& EventManager::getEvent(int eventId) const {
    return events[eventId - 1];
}

int EventManager::getTotalEvents() const {
    return (int)events.size();
}
