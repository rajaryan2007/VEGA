#pragma once
#include <vgpch.h>
#include "Event.h"



namespace VEGA {
	class VEGA_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y)
			:m_MouseX(x), m_MouseY(y) {}
		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved) 
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_MouseX, m_MouseY;

	};

	class VEGA_API MouseScrolledEvent : public Event 
	{
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {
		}

	
		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYoffset() const { return m_YOffset; }
	  std::string ToString() const override 
	  {
		  std::stringstream ss;
		  ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
		  return ss.str();
	  }
	   
	  EVENT_CLASS_TYPE(MouseScrolled)
	  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
		float m_XOffset, m_YOffset;
    };

	class VEGA_API MouseButtonEvent : public Event
	{
	public:
		inline int  GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput )
	protected:
		MouseButtonEvent(int button)
			: m_Button(button) {}
		
		int m_Button;

	};

	class VEGA_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button){ }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent" << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)




	};

	class VEGA_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {
		}

		EventType GetEventType() const override {
			return EventType::MouseButtonReleased;
		}

		const char* GetName() const override {
			return "MouseButtonReleased";
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}
	};



}
