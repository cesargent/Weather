/*
 * Copyright 2015 Przemysław Buczkowski <przemub@przemub.pl>
 * Copyright 2014 George White
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef _FORECASTVIEW_H_
#define _FORECASTVIEW_H_


#include <Bitmap.h>
#include <Button.h>
#include <GridLayout.h>
#include <GridView.h>
#include <GroupView.h>
#include <MenuBar.h>
#include <Resources.h>
#include <String.h>
#include <StringView.h>
#include <View.h>
#include <Window.h>

#include "ForecastDayView.h"
#include "PreferencesWindow.h"
#include "SelectionWindow.h"

#define CEL(T) (5.0 / 9.0) * (T - 32.0)
	// Macro converting a Fahrenheit value to a Celsius value


const uint32 kAutoUpdateMessage = 'AutU';
const uint32 kUpdateMessage = 'Upda';
const uint32 kShowForecastMessage = 'SFor';
const uint32 kSettingsMessage = 'Pref';

extern const char* kSettingsFileName;

const uint32 kSizeSmallIcon = 40;
const uint32 kSizeLargeIcon = 80;

enum weatherIconSize {
	SMALL_ICON,
	LARGE_ICON
};

class _EXPORT ForecastView;


class ForecastView : public BView {
public:
					ForecastView(BRect frame, BMessage* settings);
					ForecastView(BMessage* archive);
	virtual void	MessageReceived(BMessage* msg);
	virtual void	AttachedToWindow();
	virtual void	AllAttached();
virtual status_t	Archive(BMessage* into, bool deep = true) const;
static	BArchivable* Instantiate(BMessage* archive);
status_t			SaveState(BMessage* into, bool deep = true) const;
	void			Reload(bool forcedForecast = false);
	void			StopReload();
	void			SetCityName(BString city);
	BString			CityName();
	void			SetCityId(BString cityId);
	BString			CityId();
	void 			SetCondition(BString condition);
	void			SetUpdateDelay(int32 delay);
	int32			UpdateDelay();
	void			SetFahrenheit(bool fahrenheit);
	bool			IsFahrenheit();
	void			SetShowForecast(bool showForecast);
	bool			ShowForecast();
	void			SetTextColor(rgb_color color);
	void			SetBackgroundColor(rgb_color color);
	bool			IsDefaultColor() const;
private:
	void			_Init();
	void			_BindView();
	void			_DownloadData();
	static int32	_DownloadDataFunc(void *cookie);
	void 			_LoadBitmaps();
	BBitmap* 		_GetWeatherIcon(int32 condition, weatherIconSize size);

	status_t		_ApplyState(BMessage *settings);
	
	void			_ShowForecast(bool);
	void			_LoadIcons(BBitmap*	bitmap[2], uint32 type, const char* name);

	thread_id		fDownloadThread;
	bool 			fForcedForecast;
	BGridView* 		fView;
	BGridLayout* 	fLayout;
	bool			fReplicated;
	
	BString			fCity;
	BString			fCityId;
	int32			fUpdateDelay;
	bool			fFahrenheit;
	bool			fShowForecast;

	int32			fTemperature;
	int32			fCondition;

	SelectionWindow*	fSelectionWindow;
	PreferencesWindow* fPreferencesWindow;
	BMessageRunner*	fAutoUpdate;
	
	BBitmap* 		fAlert[2];
	BBitmap* 		fClearNight[2];
	BBitmap* 		fClear[2];
	BBitmap* 		fClouds[2];
	BBitmap* 		fFewClouds[2];
	BBitmap* 		fFog[2];
	BBitmap* 		fNightFewClouds[2];
	BBitmap* 		fRainingScattered[2];
	BBitmap* 		fRaining[2];
	BBitmap* 		fShining[2];
	BBitmap* 		fShiny[2];
	BBitmap* 		fSnow[2];
	BBitmap* 		fStorm[2];
	BBitmap* 		fThunder[2];
	BGroupView*		fInfoView;
	BGroupView*		fNumberView;
	BGroupView* 	fForecastView;
	BMenuItem*		fShowForecastMenuItem;
	BButton*		fConditionButton;
	ForecastDayView*		fForecastDayView[5];
	BStringView*	fConditionView;
	BStringView*	fTemperatureView;
	BStringView*	fCityView;
	rgb_color		fBackgroundColor;
	rgb_color		fTextColor;
};

#endif // _FORECASTVIEW_H_
