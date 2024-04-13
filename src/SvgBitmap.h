// -*- mode: c++; c-file-style: "linux"; c-basic-offset: 2; indent-tabs-mode: nil -*-
//
//  Copyright (C) 2019      Gunter Königsmann <wxMaxima@physikbuch.de>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
//
//  SPDX-License-Identifier: GPL-2.0+

/*! \file
  This file declares the class Image

  Image stores compressed images and handles scaling and uncompressing them.
*/

#ifndef SVGBITMAP_H
#define SVGBITMAP_H

#include <memory>
#include "precomp.h"
#include <wx/bitmap.h>
#include "nanosvg_private.h"
#include "nanosvgrast_private.h"
#include "cells/Cell.h"
#define NANOSVG_ALL_COLOR_KEYWORDS

/*! A wxBitmap with a constructor that generates the image from SVG.
 */
class SvgBitmap: public wxBitmap
{
public:
//! A constructor that loads the data into a wxBitmap
  SvgBitmap(wxWindow *window, const unsigned char *data, const size_t len, int width = 640, int height = 480);
  SvgBitmap(wxWindow *window, const unsigned char *data, const std::size_t len, wxSize siz);
  SvgBitmap(wxWindow *window, const wxString &data, wxSize siz);
  virtual ~SvgBitmap() override;
  SvgBitmap(SvgBitmap &&) = delete;
  SvgBitmap &operator=(SvgBitmap &&o) noexcept;

  //! Sets the bitmap to a new size and renders the svg image at this size.
  const SvgBitmap& SetSize(int width, int height);
  //! Sets the bitmap to a new size and renders the svg image at this size.
  const SvgBitmap& SetSize(wxSize siz){return SetSize(siz.x, siz.y);}
  //! Gets the original size of the svg image
  wxSize GetOriginalSize() const
    { return m_svgImage ? wxSize(m_svgImage->width, m_svgImage->height) : wxDefaultSize; }
  /*! An "invalid bitmap" sign */
  wxBitmap GetInvalidBitmap(int targetSize);
private:
  //! No idea what nanoSVG stores here. But can be shared between images.
  static struct wxm_NSVGrasterizer* m_svgRast;
  //! The renderable svg image after we have read it in
  std::unique_ptr<wxm_NSVGimage, decltype(std::free)*> m_svgImage{nullptr, std::free};
  //! The window this bitmap will be drawn o
  wxWindow *m_window = NULL;
};

#endif // SVGBITMAP_H
