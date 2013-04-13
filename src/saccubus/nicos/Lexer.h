/**
 * Saccubus
 * Copyright (C) 2013 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include <string>

namespace saccubus {

template <typename E, typename A> class Left;
template <typename E, typename A> class Right;
template <typename E, typename A>
struct Either {
	virtual Left<E,A>* left(){ return nullptr; };
	virtual Right<E,A>* right(){ return nullptr; };
	virtual ~Either() noexcept = 0;
};

template <typename E, typename A>
struct Left : public Either <E,A> {
	E const val;
	Left (E const& e):val(e){};
	virtual Left<E,A>* left(){ return this; };
	virtual ~Left() noexcept = default;
};


template <typename E, typename A>
struct Right : public Either <E,A> {
	A val;
	Right(T const& t):val(t){}
	virtual ~Right() noexcept = default;
	virtual Right<E,A>* right(){ return this; };
};

// >>=
template <typename E, typename A1, typename A2>
Either<E, A2> operator >= (Either<E,A1> const& r, std::function<Either<E,A2>(A1)> const& f)
{
	return r.left() ?
			Left<E, A2>(r.left()->val) :
			f( r.right()->val );
}

// >>
template <typename E, typename A1, typename A2>
Left<E, A2> operator >> (Either<E,A1> const& r, Either<E,A2> const& f)
{
	return r.left() ?
			Left<E, A2>(r.val) :
			f;
}

template <typename E, typename A1>
Right<E, A1> ret (A1 const& a)
{
	return Right<E,A1>(a);
}


}
