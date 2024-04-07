/*
 * led.h
 *
 *  Created on: Jul 16, 2021
 *      Author: rickweil
 */

#ifndef INC_TELLER_H_
#define INC_TELLER_H_

extern Teller tellers[4];

void initialize_tellers(void);
void manage_tellers(void);
#endif /* INC_TELLER_H_ */
