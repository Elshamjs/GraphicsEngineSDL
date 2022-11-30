#pragma once

#ifndef TRANSLATE_TRANSITION_H
#define TRANSLATE_TRANSITION_H

// Agarra un target, lo mueve con: una duración, velocidad y animación especificada
class TranslateTransition : public Transition
{
public:
	~TranslateTransition();
	TranslateTransition(VObject* target, float from_x, float from_y, float to_x, float to_y, float duration_s);
	TranslateTransition(VObject* target, float from_x, float from_y, float to_x, float to_y, float duration_s, function<void()> on_finish);
	TranslateTransition(VObject* target, float from_x, float from_y, float to_x, float to_y, float duration_s, int delay_millis);
	TranslateTransition(VObject* target, float from_x, float from_y, float to_x, float to_y, float duration_s, int delay_millis, function<void()> on_finish);
	void play();
private:
	void continue_process();
	float to_x;
	float to_y;
	float from_x;
	float from_y;
};
#endif