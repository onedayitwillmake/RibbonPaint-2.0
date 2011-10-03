

#include "cinder/app/AppBasic.h"
#include "cinder/app/KeyEvent.h"
#include "cinder/Area.h"
#include "cinder/Camera.h"
#include "cinder/DataSource.h"
#include "cinder/Font.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/params/Params.h"
#include "cinder/Path2d.h"
#include "cinder/Perlin.h"
#include "cinder/Rand.h"
#include "cinder/Url.h"
#include "cinder/Utilities.h"
#include "cinder/Xml.h"

// app
#include "IKLine.h"
#include "Resources.h"
#include "ColorStateManager.h"
#include "IColorMode.h"
#include "ColorModes/ColorModeAlphaBlend1.h"
#include "ColorModes/ColorModeAlphaBlend2.h"
#include "ColorModes/ColorModeAlphaBlend3.h"
#include "ColorModes/ColorModeGrayscale.h"
#include "ColorModes/ColorModeHSV.h"
#include "ColorModes/ColorModeRGB.h"
#include "ColorModes/ColorModeRGB2.h"
#include "ColorModes/ColorModeRGB3.h"
#include "ColorModes/ColorModeRGBInverse.h"

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/regex.hpp>
#include <boost/smart_ptr.hpp>
// Absolute imports
#include <vector>


enum
{
	COLORMODE_HSV = 1,
	COLORMODE_RGBINVERSE = 2,
	COLORMODE_RGB = 3,
	COLORMODE_RGB_B = 4,
	COLORMODE_RGB_C = 5,
	COLORMODE_GRAYSCALE = 6,
	COLORMODE_ALPHABLEND_1 = 7,
	COLORMODE_ALPHABLEND_2 = 8,
	COLORMODE_ALPHABLEND_3 = 9,
};

enum
{
	kStateIsShowingSplashScreen,
	kStateNormal
};

//using namespace std;
//using namespace ci::app;
//using namespace boost::posix_time;

typedef boost::shared_ptr<IKLine> linePointer;

// We'll create a new Cinder Application by deriving from the AppBasic class
class RibbonPaint : public ci::app::AppBasic
{
public:
	// Cinder events
	void prepareSettings( ci::app::AppBasic::Settings *settings);
	void setup();
	void setupAfterSplash();
	void update();
	
	// UIEvents
	void keyDown( ci::app::KeyEvent event );
	void keyUp( ci::app::KeyEvent event);
	void mouseUp( ci::Vec2f position );
	void mouseDown( ci::Vec2f position );
	void mouseDrag( ci::Vec2f position );
	void mouseMove( ci::Vec2f position );

#ifndef __RIBBON__PAINT__XCODE__
	void mouseUp( ci::app::MouseEvent event );
	void mouseDown( ci::app::MouseEvent event );
	void mouseDrag( ci::app::MouseEvent event );
	void mouseMove( ci::app::MouseEvent event );
#endif

	void fileDrop( ci::app::FileDropEvent event );
	// Files
	void saveOutBrushImageAndParameters();
	// Creation / Deletion
	void randomizeBrush();
	void setBrushSettingsFromStringParameters( std::string currentLine );
	void createBrush();
	// Drawing events
	void draw();
	void drawIKLine(linePointer& lineToDraw);
	void drawBezier(ci::Vec2f origin, ci::Vec2f control, ci::Vec2f destination, int segments);
	// Utils
	template <class T> inline std::string toString(const T& t);
	void updateParams();
	void displayAlertString(std::string textToDisplay);
	

	ci::Area _getWindowBounds();
	ci::Vec2f _getWindowCenter();
	int _getWindowWidth();
	int _getWindowHeight();
	int _getElapsedFrames();
	bool _getIsShiftDown();
	
	ci::Vec2f						_mousePosition;
	ci::Perlin						_perlinNoise;
	std::vector<linePointer>		_lines;
	
	// STATES
	ColorModes::ColorStateManager _colorStateManager;
	std::map<char, ColorModes::IColorMode*> _colorMap;

	int		_state;
	bool	_drawLines;
	bool	_drawParams;
	bool	_useBezier;
	bool	_additiveBlending; // Affected by _colorMode but not settable.
	bool	_glitchSegment;
	bool	_drawPins;
	
	int		_alertTextDisplayTimer;
	int		_alertTextDefaultDisplayTimeInFrames;
	std::string	_alertTextString;
	
	// Behavior modifiers
	double	_oldAlphaWhenDrawing;
	double	_alphaWhenDrawing;
	float	_alphaWhenDrawingFloat;
	float	_mouseChaseDamping;
	
	// BRUSH PROPERTIES
	int		_bristleCount;
	float	_gravity;
	float	_filamentSpacing;
	float	_filamentCount;
	float	_brushRadius;
	float	_canvasFrictionMin;
	float	_canvasFrictionMax;
//	int		_colorMode;

	// Version checking
	float				_versionNumber;
	float				_latestVersion;
	int					_versionFlasher;
	ci::IStreamUrlRef	_versionCheckUrlRef;
	
//#define __COLORMODE__TEST
#ifdef __COLORMODE__TEST
	float __R_LEFT, __R_RIGHT;
	float __G_LEFT, __G_RIGHT;
	float __B_LEFT, __B_RIGHT;
	float __RGB_ALPHA;
#endif
};
