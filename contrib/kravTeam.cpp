/*
	Test tasks for the team project
	Circles by krav-team
	Version 1.0
	Made by krav-team
*/
#include "kravTeam.h"

void renderCircles(sf::RenderWindow &window)
{
	circleByKrav krav({ 10.f, 10.f });
	circle lastic(120, 10);
	circleByRus rus(330, 10, 50);
	CircleBySemitro semitro({ 440.f, 10.f }, 50);
	SlonCircle slon({ 550, 10, 50 });

	window.draw(krav.getShape());
	lastic.render(window);
	rus.CircleDraw(window);
	semitro.render(window);
	slon.draw(window);
};
