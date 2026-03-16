#pragma once



namespace VEGA
{
	class VEGA_API GraphicsContext 
	{
	public:
		virtual void Init() = 0;
 	    virtual void SwapBuffers() = 0;


	};
}