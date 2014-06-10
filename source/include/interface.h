#ifndef INTERFACE_H
#define INTERFACE_H

#include <QtPlugin>
#include <QString>

class ComInterface
{
public:
	virtual ~ComInterface() {}

	virtual QString name() const = 0;
};

Q_DECLARE_INTERFACE(ComInterface, "org.galaxyworld.plugins.ComInterface/1.0")

#endif // INTERFACE_H