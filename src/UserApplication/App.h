/*
 * App.h
 *
 *  Created on: 2016/08/22
 *      Author: Matsutomo2
 */

#ifndef USERAPPLICATION_APP_H_
#define USERAPPLICATION_APP_H_

#ifdef __cplusplus
extern "C" {
#endif

void Initialize();

void MainLoop();

void _SystemClockCallBack();

#ifdef __cplusplus
}
#endif

#endif /* USERAPPLICATION_APP_H_ */
