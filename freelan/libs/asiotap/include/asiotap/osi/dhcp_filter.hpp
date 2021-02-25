/*
 * libasiotap - A portable TAP adapter extension for Boost::ASIO.
 * Copyright (C) 2010-2011 Julien KAUFFMANN <julien.kauffmann@freelan.org>
 *
 * This file is part of libasiotap.
 *
 * libasiotap is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * libasiotap is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 *
 * If you intend to use libasiotap in a commercial software, please
 * contact me : we may arrange this for a small fee or no fee at all,
 * depending on the nature of your project.
 */

/**
 * \file dhcp_filter.hpp
 * \author Julien KAUFFMANN <julien.kauffmann@freelan.org>
 * \brief A DHCP filter class.
 */

#pragma once

#include "filter.hpp"
#include "dhcp_frame.hpp"

#include "bootp_helper.hpp"
#include "dhcp_helper.hpp"

namespace asiotap
{
	namespace osi
	{
		/**
		 * \brief The DHCP filter.
		 */
		template <typename ParentFilterType>
		class filter<dhcp_frame, ParentFilterType> : public _filter<dhcp_frame, ParentFilterType>
		{
			public:

				/**
				 * \brief Constructor.
				 * \param _parent The parent filter.
				 */
				filter(ParentFilterType& _parent) :
					_filter<dhcp_frame, ParentFilterType>(_parent)
				{}
		};

		/**
		 * \brief The frame parent match function.
		 * \param parent The parent frame.
		 * \return true if the frame matches the parent frame.
		 */
		template <>
		inline bool frame_parent_match<dhcp_frame>(const_helper<bootp_frame> parent) {
			return (boost::asio::buffer_size(parent.options()) >= sizeof(DHCP_MAGIC_COOKIE));
		}

		/**
		 * \brief Check if a frame is valid.
		 * \param frame The frame.
		 * \return true on success.
		 */
		inline bool check_frame(const_helper<dhcp_frame> frame) {
			return (frame.magic_cookie() == DHCP_MAGIC_COOKIE) && frame.check_options();
		}
	}
}