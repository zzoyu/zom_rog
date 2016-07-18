#ifndef	__VECTOR_2D_H__
#define __VECTOR_2D_H__

#include <math.h>

class Vector2D
{
private:
	float m_fX, m_fY;

public:
	Vector2D( float _fX, float _fY ) : m_fX(_fX), m_fY(_fY) {}
	Vector2D(){}

	float GetX (){ return m_fX; } const
	float GetY (){ return m_fY; } const

	void SetX( float _fX ){ m_fX = _fX; }
	void SetY( float _fY ){ m_fY = _fY; }

	float GetLength(){ return sqrt( m_fX * m_fX + m_fY * m_fY ); }

	void Normalize()
	{
		float length = GetLength();

		if( length > 0 )
		{
			(*this) *= 1 / length;
		}
	}

	Vector2D operator+( const Vector2D& v2 ) const
	{
		return Vector2D( m_fX+v2.m_fX, m_fY+v2.m_fY );
	}

	friend Vector2D operator+=( Vector2D& v1, const Vector2D& v2 )
	{
		v1.m_fX += v2.m_fX;
		v1.m_fY += v2.m_fY;

		return v1;
	}

	Vector2D operator-( const Vector2D& v2 ) const
	{
		return Vector2D( m_fX-v2.m_fX, m_fX-v2.m_fY );
	}

	friend Vector2D operator-=( Vector2D& v1, const Vector2D& v2 )
	{
		v1.m_fX -= v2.m_fX;
		v1.m_fY -= v2.m_fY;

		return v1;
	}

	Vector2D operator*( float _fScalar ) const
	{
		return Vector2D( m_fX * _fScalar, m_fY*_fScalar );
	}

	Vector2D operator*=( float _fScalar )
	{
		m_fX *= _fScalar;
		m_fY *= _fScalar;

		return *this;
	}

	Vector2D operator/( float _fScalar ) const
	{
		return Vector2D( m_fX/_fScalar, m_fY/_fScalar );
	}

	Vector2D operator/=( float _fScalar )
	{
		m_fX /= _fScalar;
		m_fY /= _fScalar;

		return *this;
	}
};

#endif