/*
 * led.h
 *
 *  Created on: Jul 16, 2021
 *      Author: rickweil
 */

#ifndef INC_TELLER_H_
#define INC_TELLER_H_

extern Teller tellers[3];

void init_teller(int i);
void manage_teller(int i);
#endif /* INC_TELLER_H_ */
