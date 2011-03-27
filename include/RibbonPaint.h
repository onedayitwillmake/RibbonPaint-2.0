#include "cinder/app/AppBasic.h"
#include "cinder/params/Params.h"
#include "cinder/Font.h"
#include "cinder/Utilities.h"
#include "cinder/ImageIo.h"
#include "cinder/Path2d.h"
#include "cinder/Rand.h"
#include "cinder/app/KeyEvent.h"
#include "cinder/Camera.h"
#include "cinder/gl/Texture.h"
#include "cinder/Perlin.h"
#include "cinder/Url.h"
#include "cinder/DataSource.h"
#include "cinder/Xml.h"


// Absolute imports
#include <vector>
#include <boost/regex.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

// app
#include "IKLine.h"
#include "Resources.h"

#define trace(__X__) console() << __X__ << std::endl;


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
	void mouseUp( ci::app::MouseEvent event );
	void mouseDown( ci::app::MouseEvent event );
	void mouseDrag( ci::app::MouseEvent event );
	void mouseMove( ci::app::MouseEvent event );
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
	// Colors and states
	void toggleAdditiveBlending( bool enableAdditiveBlending );
	void getColorMode(double inverseI, double alpha);
	// Utils
	template <class T> inline std::string toString(const T& t);
	void updateParams();
	void displayAlertString(std::string textToDisplay);
	
	ci::params::InterfaceGl		_params;
	ci::gl::Texture				_splashScreen;
	ci::gl::Texture				_instructionsWhite;
	ci::gl::Texture				_instructionsBlack;
	
	ci::Vec2f					_mousePosition;
	ci::Colorf					_clearColor;
	ci::Perlin					_perlinNoise;
	std::vector<linePointer>		_lines;
	
	// STATES
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
	int		_colorMode;

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

#pragma mark Help Functions
float round(float d)
{
	return floor(d + 0.5);
}

inline void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v )
{
	int i;
	float f, p, q, t;
	if( s == 0 ) {
		// achromatic (grey)
		*r = *g = *b = v;
		return;
	}
	h /= 60;			// sector 0 to 5
	i = floor( h );
	f = h - i;			// factorial part of h
	p = v * ( 1 - s );
	q = v * ( 1 - s * f );
	t = v * ( 1 - s * ( 1 - f ) );
	
	switch( i )
	{
		case 0:
			*r = v;
			*g = t;
			*b = p;
			break;
		case 1:
			*r = q;
			*g = v;
			*b = p;
			break;
		case 2:
			*r = p;
			*g = v;
			*b = t;
			break;
		case 3:
			*r = p;
			*g = q;
			*b = v;
			break;
		case 4:
			*r = t;
			*g = p;
			*b = v;
			break;
		default:		// case 5:
			*r = v;
			*g = p;
			*b = q;
			break;
	}
}
