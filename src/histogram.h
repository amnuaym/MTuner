//--------------------------------------------------------------------------//
/// Copyright (c) 2017 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#ifndef __RTM_MTUNER_HISTOGRAM_H__
#define __RTM_MTUNER_HISTOGRAM_H__

class HistogramView;

struct HistogramToolTip
{
	QRectF	m_rect;
	QString	m_text;
	int		m_bin;

	HistogramToolTip() {}
	HistogramToolTip(const QRect& _rect, const QString& _string, int _bin) :
		m_rect(_rect),
		m_text(_string),
		m_bin(_bin)
	{}
};

struct DisplayMode
{
	enum Enum
	{
		Global,
		Snapshot,
		Both
	};
};

struct HistogramType
{
	enum Enum
	{
		Size,
		Overhead,
		Count
	};
};

class Histogram : public QGraphicsItem
{
private:
	HistogramView*				m_histogramWidget;
	DisplayMode::Enum			m_displayMode;
	HistogramType::Enum			m_type;
	bool						m_showPeaks;
	QVector<HistogramToolTip>	m_toolTips;
	QPoint						m_highlight;
	int							m_highlightBin;
	QLocale						m_locale;

public:
	Histogram(HistogramView* _graphWidget);

	void parentResized() { prepareGeometryChange(); }
	void setDisplayMode(DisplayMode::Enum _mode) { m_displayMode = _mode; parentResized(); }
	void setHistogramType(HistogramType::Enum _type) { m_type = _type; parentResized(); }
	void setPeaks(bool _show) { m_showPeaks = _show; parentResized(); }
	void setHighlight(const QPoint& _point, int _binIndex) { m_highlight = _point; m_highlightBin = _binIndex; parentResized(); }
	int  getHighlightIndex() const { return m_highlightBin; }

	const QVector<HistogramToolTip>&	getTooltips() const { return m_toolTips; }

	/// QWidget
	virtual QRectF			boundingRect() const;
	virtual QPainterPath	shape() const;
	virtual void			paint(QPainter* _painter, const QStyleOptionGraphicsItem* _option, QWidget* _widget);

private:
	QString		fromVal(int _val);
	uint64_t	getMaxValue(rtm::MemoryStats& _stats, HistogramType::Enum _type, bool _usePeak);
	uint64_t	getValue(rtm::MemoryStats& _stats, HistogramType::Enum _type, int _bin, bool _peak);
	QString		getTypeString(HistogramType::Enum _type, uint64_t _val, bool _peak);
};

#endif // __RTM_MTUNER_HISTOGRAM_H__
