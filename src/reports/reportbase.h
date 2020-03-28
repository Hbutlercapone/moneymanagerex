/*******************************************************
 Copyright (C) 2006 Madhan Kanagavel

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ********************************************************/

//----------------------------------------------------------------------------
#ifndef MM_EX_REPORTBASE_H_
#define MM_EX_REPORTBASE_H_
//----------------------------------------------------------------------------
#include "mmDateRange.h"
#include "option.h"
#include "model/Model_Report.h"
class wxString;
class wxArrayString;
//----------------------------------------------------------------------------

class mmPrintableBase
{
public:
    mmPrintableBase(const wxString& title);
    virtual ~mmPrintableBase();
    virtual wxString getHTMLText() = 0;
    virtual void RefreshData() {}
	virtual const wxString getReportTitle() const;
	virtual const wxString getFileName() const;
    virtual int report_parameters() { return RepParams::NONE; }
    void date_range(const mmDateRange* date_range, int selection);
    void initial_report(bool initial) { m_initial = initial; }

    int getDateSelection() const;
    int getAccountSelection() const;
    int getChartSelection() const;
    const wxString getAccountNames() const;
    void chart(int selection);
    void setAccounts(int selection, const wxString& name);
    void setSelection(int sel);

protected:
    wxString m_title;
    const mmDateRange* m_date_range;
    bool m_initial;
    int m_date_selection;
    int m_chart_selection;
    const wxArrayString* accountArray_;
    bool m_only_active;
    wxString m_settings;
    wxDateTime m_begin_date;
    wxDateTime m_end_date;
    int m_account_selection;

public:
    static const char * m_template;
    enum RepParams
    {
        NONE = 0
        , SINGLE_DATE = 1
        , DATE_RANGE = 2
        , BUDGET_DATES = 4
        , ONLY_YEARS = 8
        , ACCOUNTS_LIST = 16
        , CHART = 32
    };
};

inline void mmPrintableBase::setSelection(int sel) { m_date_selection = sel; }
inline int mmPrintableBase::getDateSelection() const { return this->m_date_selection; }
inline int mmPrintableBase::getAccountSelection() const { return this->m_account_selection; }
inline int mmPrintableBase::getChartSelection() const { return this->m_chart_selection; }
inline void mmPrintableBase::chart(int selection) { m_chart_selection = selection; }

class mmGeneralReport : public mmPrintableBase
{
public:
    explicit mmGeneralReport(const Model_Report::Data* report);

public:
    wxString getHTMLText();
    virtual int report_parameters();

private:
    const Model_Report::Data* m_report;
};

class mmPrintableBaseSpecificAccounts : public mmPrintableBase
{
public:
    explicit mmPrintableBaseSpecificAccounts(const wxString& report_name, int sort_column = 0);
    virtual ~mmPrintableBaseSpecificAccounts();

protected:
    const wxArrayString* accountArray_;

    void getSpecificAccounts();
};

#include "html_template.h"
class mm_html_template: public html_template
{
public:
    explicit mm_html_template(const wxString & arg_template);

private:
    void load_context();
};



//----------------------------------------------------------------------------
#endif // MM_EX_REPORTBASE_H_
