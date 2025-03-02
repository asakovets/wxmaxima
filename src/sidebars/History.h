// -*- mode: c++; c-file-style: "linux"; c-basic-offset: 2; indent-tabs-mode: nil -*-
//
//  Copyright (C) 2009-2015 Andrej Vodopivec <andrej.vodopivec@gmail.com>
//            (C) 2014-2015 Gunter Königsmann <wxMaxima@physikbuch.de>
//            (C) 2020      Kuba Ober <kuba@bertec.com>
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

  This file contains the definition of the class History that handles the recently
  issued commands for the history pane.
*/

#ifndef HISTORY_H
#define HISTORY_H

#include "precomp.h"
#include "RegexCtrl.h"
#include <wx/wx.h>
#include <wx/regex.h>
#include <vector>
#include <wx/arrstr.h>
enum
{
  history_ctrl_id = 1,
  history_regex_id,
  export_all,
  export_session,
  export_visible,
  export_selected,
  toggle_ShowCurrentSessionOnly,
  clear_selection,
  clear_history
};

/*! This class generates a pane containing the last commands that were issued.

 */
class History final : public wxPanel
{
public:
  History(wxWindow *parent, int id, Configuration *cfg);

  //! The destructor
  ~History();

  //! Add a file to the recently opened files list.
  void AddToHistory(const wxString &cmd);

  //! Called if the filter text or method changes
  void OnRegExEvent(wxCommandEvent &ev);

  //! Apply all filters and refresh the display
  void RebuildDisplay();

  /*! Get the currently selected command and advance the selection

    \param next
      - true: Advance the current selection by one
      - false: Advance the current selection by -1
   */
  wxString GetCommand(bool next);

  //! Is called when a new maxima session starts
  void MaximaSessionStart();

  //! Actually update the history sidebar. Called when no other work is to be done.
  bool UpdateDeferred();
  //! Where to save thi history
  void SetSavePlace(const wxString &saveplace);

private:
  //! Called on right-clicks on the history panel
  void OnMouseRightDown(wxMouseEvent &event);
  //! Called if the user calls on a menu item
  void OnMenu(wxCommandEvent &event);

  void UnselectAll() const;
  void SetCurrent(long current);

  wxString m_saveplace;
  //! How many commands in the history are from the current session?
  size_t m_sessionCommands = 0;
  wxListBox *m_history;
  RegexCtrl *m_regex;
  std::vector<wxString> m_commands;
  //! Commands we want to add to the history sidebar, once we have time to
  wxArrayString m_deferredCommands;
  //! The currently selected item. -1=none.
  long m_current = 0;
  wxString m_regex_Old;
  //! Show only commands from the current session?
  bool m_showCurrentSessionOnly = true;
  //! The config key telling where to store m_showCurrentSessionOnly between sessions
  static wxString m_showCurrentSessionOnlyKey;
};

#endif // HISTORY_H
