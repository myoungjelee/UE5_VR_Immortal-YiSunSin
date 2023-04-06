// Fill out your copyright notice in the Description page of Project Settings.


#include "EasingLibrary.h"


float UEasingLibrary::QuadEaseIn(float Param)
{
	return Param * Param;
}

float UEasingLibrary::QuadEaseOut(float Param)
{
	return -(Param * (Param - 2.f));
}

float UEasingLibrary::QuadEaseInOut(float Param)
{
	if (Param < 0.5f) return 2.f * Param * Param;
	return (-2.f * Param * Param) + (4.f * Param) - 1.f;
}

float UEasingLibrary::CubicEaseIn(float Param)
{
	return Param * Param * Param;
}

float UEasingLibrary::CubicEaseOut(float Param)
{
	float P = Param - 1.f;
	return P * P * P + 1.f;
}

float UEasingLibrary::CubicEaseInOut(float Param)
{
	if (Param < 0.5f) return 4.f * Param * Param * Param;
	float P = (2.f * Param) - 2.f;
	return 0.5f * P * P * P + 1.f;
}

float UEasingLibrary::QuartEaseIn(float Param)
{
	return Param * Param * Param * Param;
}

float UEasingLibrary::QuartEaseOut(float Param)
{
	float P = Param - 1.f;
	return P * P * P * (1.f - Param) + 1.f;
}

float UEasingLibrary::QuartEaseInOut(float Param)
{
	if (Param < 0.5f) return 8.f * Param * Param * Param * Param;
	float P = Param - 1.f;
	return -8.f * P * P * P * P + 1.f;
}

float UEasingLibrary::QuintEaseIn(float Param)
{
	return Param * Param * Param * Param * Param;
}

float UEasingLibrary::QuintEaseOut(float Param)
{
	float P = Param - 1.f;
	return P * P * P * P * P + 1.f;
}

float UEasingLibrary::QuintEaseInOut(float Param)
{
	if (Param < 0.5f) return 16.f * Param * Param * Param * Param * Param;
	float P = (2.f * Param) - 2.f;
	return 0.5f * P * P * P * P * P + 1.f;
}

float UEasingLibrary::SineEaseIn(float Param)
{
	return FMath::Sin((Param - 1.f) * (PI / 2.f)) + 1.f;
}

float UEasingLibrary::SineEaseOut(float Param)
{
	return FMath::Sin(Param * (PI / 2.f));
}

float UEasingLibrary::SineEaseInOut(float Param)
{
	return 0.5f * (1.f - FMath::Cos(Param * PI));
}

float UEasingLibrary::CircEaseIn(float Param)
{
	return 1.f - FMath::Sqrt(1.f - (Param * Param));
}

float UEasingLibrary::CircEaseOut(float Param)
{
	return FMath::Sqrt((2.f - Param) * Param);
}

float UEasingLibrary::CircEaseInOut(float Param)
{
	if (Param < 0.5f) return 0.5f * (1.f - FMath::Sqrt(1.f - 4.f * (Param * Param)));
	return 0.5f * (FMath::Sqrt(-((2.f * Param) - 3.f) * ((2.f * Param) - 1.f)) + 1.f);
}

float UEasingLibrary::ExpoEaseIn(float Param)
{
	return (Param == 0.f) ? Param : FMath::Pow(2.f, 10.f * (Param - 1.f));
}

float UEasingLibrary::ExpoEaseOut(float Param)
{
	return (Param == 1.f) ? Param : 1.f - FMath::Pow(2.f, -10.f * Param);
}

float UEasingLibrary::ExpoEaseInOut(float Param)
{
	if (Param == 0.f || Param == 1.f) return Param;
	if (Param < 0.5f) return 0.5f * FMath::Pow(2.f, (20.f * Param) - 10.f);
	return -0.5f * FMath::Pow(2.f, (-20.f * Param) + 10.f) + 1.f;
}

float UEasingLibrary::ElasticEaseIn(float Param)
{
	return FMath::Sin(13.f * (PI / 2.f) * Param) * FMath::Pow(2.f, 10.f * (Param - 1.f));
}

float UEasingLibrary::ElasticEaseOut(float Param)
{
	return FMath::Sin(-13.f * (PI / 2.f) * (Param + 1)) * FMath::Pow(2.f, -10.f * Param) + 1.f;
}

float UEasingLibrary::ElasticEaseInOut(float Param)
{
	if (Param < 0.5f) return 0.5 * FMath::Sin(13.f * (PI / 2.f) * (2 * Param)) * FMath::Pow(2.f, 10.f * ((2.f * Param) - 1.f));
	return 0.5f * (FMath::Sin(-13.f * (PI / 2.f) * ((2.f * Param - 1.f) + 1.f)) * FMath::Pow(2.f, -10.f * (2.f * Param - 1.f)) + 2.f);
}

float UEasingLibrary::BackEaseIn(float Param)
{
	return Param * Param * Param - Param * FMath::Sin(Param * PI);
}

float UEasingLibrary::BackEaseOut(float Param)
{
	float P = 1.f - Param;
	return 1.f - (P * P * P - P * FMath::Sin(P * PI));
}

float UEasingLibrary::BackEaseInOut(float Param)
{
	if (Param < 0.5f)
	{
		float P = 2.f * Param;
		return 0.5f * (P * P * P - P * FMath::Sin(P * PI));
	}

	float P = (1.f - (2.f * Param - 1.f));
	return 0.5f * (1.f - (P * P * P - P * FMath::Sin(P * PI))) + 0.5f;
}

float UEasingLibrary::BounceEaseIn(float Param)
{
	return 1.f - BounceEaseOut(1.f - Param);
}

float UEasingLibrary::BounceEaseOut(float Param)
{
	if (Param < 4.f / 11.f) return (121.f * Param * Param) / 16.f;
	if (Param < 8.f / 11.f) return (363.f / 40.f * Param * Param) - (99.f / 10.f * Param) + 17.f / 5.f;
	if (Param < 9.f / 10.f) return (4356.f / 361.f * Param * Param) - (35442.f / 1805.f * Param) + 16061.f / 1805.f;
	return (54.f / 5.f * Param * Param) - (513.f / 25.f * Param) + 268.f / 25.f;
}

float UEasingLibrary::BounceEaseInOut(float Param)
{
	if (Param < 0.5f) return 0.5f * BounceEaseIn(Param * 2.f);
	return 0.5f * BounceEaseOut(Param * 2.f - 1.f) + 0.5f;
}