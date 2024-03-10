// -*- mode: c++; c-file-style: "linux"; c-basic-offset: 2; indent-tabs-mode: nil -*-
//
//  Copyright (C) 2004-2015 Andrej Vodopivec <andrej.vodopivec@gmail.com>
//            (C) 2012 Doug Ilijev <doug.ilijev@gmail.com>
//            (C) 2014-2015 Gunter Königsmann <wxMaxima@physikbuch.de>
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

/*!\file
  This file declares the class StatSidebar, that provides some statistics buttons.
*/
#ifndef DRAWSIDEBAR_H
#define DRAWSIDEBAR_H

#include "precomp.h"
#include <wx/wx.h>
#include <wx/button.h>
#include "EventIDs.h"
#include "ButtonWrapSizer.h"
#include <wx/panel.h>

//! The class for the sidebar with the draw commands
class DrawSidebar: public wxScrolled<wxPanel>
{
public:
  explicit DrawSidebar(wxWindow *parent, int id = wxID_ANY);
  /*! Tell the sidebar if we currently are inside a 2D or a 3D plot command

    \param dimensions
    - 0 = We aren't inside a plot
    - 2 = We are inside a 2D plot
    - 3 = We are inside a 3D plot
  */
  void SetDimensions(int dimensions);
  int  GetDimensions() const { return m_dimensions; }
protected:
  void OnSize(wxSizeEvent &event);
private:
  Buttonwrapsizer *m_grid;
  wxButton *m_draw_setup2d;
  wxButton *m_draw_setup3d;
  wxButton *m_draw_explicit;
  wxButton *m_draw_implicit;
  wxButton *m_draw_parametric;
  wxButton *m_draw_points;
  wxButton *m_draw_fgcolor;
  wxButton *m_draw_fillcolor;
  wxButton *m_draw_title;
  wxButton *m_draw_key;
  wxButton *m_draw_grid;
  wxButton *m_draw_axis;
  wxButton *m_draw_contour;
  wxButton *m_draw_accuracy;
  int m_dimensions;
};

#endif // DRAWSIDEBAR_H
