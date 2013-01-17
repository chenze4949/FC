-- Lua FCView object class

FCView = {}
FCView.nextName = 1

function FCView:New( name, classType, parent )
	ret = {}
	ret.classType = classType
	ret.subviews = {}

	if name == nil then
		ret.name = "view" .. FCView.nextName
		FCView.nextName = FCView.nextName + 1
	else
		ret.name = name
	end

	if parent ~= nil then
		FCViewManager.CreateView( ret.name, classType, parent.name )
	else
		FCViewManager.CreateView( ret.name, classType, nil )
	end

	-- setup the metatable entries

	setmetatable( ret, self )
	self.__index = self
	self.__newindex = function() error() end

	return ret
end

function FCView:Destroy()
	FCViewManager.DestroyView( self.name )
end

function FCView:SetBackgroundColor( color )
	if color.class ~= "FCColor" then
		FCError( "FCView:SetColor() with a non-FCColor color: " .. self.name )
		return
	end
	FCViewManager.SetBackgroundColor( self.name, color )
end

function FCView:SetFrame( frame, duration )
	--FCLog("Setting frame:" .. self.name)
	if frame.class ~= "FCRect" then
		FCError( "FCView:SetFrame() with a non-FCRect frame: " .. self.name )
		return
	end
	self.frame = frame
	FCViewManager.SetFrame( self.name, frame, duration )

	-- layout subviews

	for _,sub in pairs(self.subviews) do
		if sub.frame ~= nil then
			--FCLog("Setting subframe:" .. sub.name)
			sub:SetFrame( sub.frame, duration )
		end
	end
end

function FCView:GetFrame()
	return FCViewManager.GetFrame( self.name )
end

function FCView:SetAlpha( alpha, duration )
	FCViewManager.SetAlpha( self.name, alpha, duration )
end

function FCView:ShrinkFontToFit( )
	FCViewManager.ShrinkFontToFit( self.name )
end

function FCView:SetText( text )
	FCViewManager.SetText( self.name, text )
end

function FCView:SetTextColor( color )
	if color.class ~= "FCColor" then
		FCError( "FCView:SetTextColor() with a non-FCColor color: " .. self.name )
	end
	FCViewManager.SetTextColor( self.name, color )
end

function FCView:SetImage( image )
	FCViewManager.SetImage( self.name, image )
end

function FCView:SetOnSelectLuaFunction( func )
	FCViewManager.SetOnSelectLuaFunction( self.name, func )
end

function FCView:SetIntegerProperty( prop, value )
	FCViewManager.SetViewPropertyInteger( self.name, prop, value )
end

function FCView:SetStringProperty( prop, value )
	FCViewManager.SetViewPropertyString( self.name, prop, value )
end

function FCView:SetTapFunction( value )
	--FCViewManager.SetViewPropertyString( self.name, "tapFunction", value )
	FCViewManager.SetTapFunction( self.name, value )
end

function FCView:MoveToFront()
	FCViewManager.MoveViewToFront( self.name )
end

function FCView:MoveToBack()
	FCViewManager.MoveViewToBack( self.name )
end

function FCView:SetContentMode( mode )
	FCViewManager.SetViewPropertyInteger( self.name, "contentMode", mode )
end

function FCView:SetTextAlignment( mode )
	FCViewManager.SetViewPropertyInteger( self.name, "textAlignment", mode )
end

function FCView:SetFontWithSize( font, size )
	FCViewManager.SetViewPropertyString( self.name, "fontName", font )
	FCViewManager.SetViewPropertyFloat( self.name, "fontSize", size )
end

-------------------------------------------------------------------------------------
-- Constants
-------------------------------------------------------------------------------------

-- NOTE: These MUST mach the C counterparts

kFCImageView = "FCImageView"
kFCLabelView = "FCLabelView"
kFCTextView = "FCTextView"
kFCContainerView = "FCContainerView"
kFCGLView = "FCGLView"

kFCViewContentModeScaleToFill = 1
kFCViewContentModeScaleAspectFit = 2
kFCViewContentModeScaleAspectFill = 3
kFCViewContentModeRedraw = 4
kFCViewContentModeCenter = 5
kFCViewContentModeTop = 6
kFCViewContentModeBottom = 7
kFCViewContentModeLeft = 8
kFCViewContentModeRight = 9
kFCViewContentModeTopLeft = 10
kFCViewContentModeTopRight = 11
kFCViewContentModeBottomLeft = 12
kFCViewContentModeBottomRight = 13

kFCViewTextAlignmentLeft = 1
kFCViewTextAlignmentCenter = 2
kFCViewTextAlignmentRight = 3


