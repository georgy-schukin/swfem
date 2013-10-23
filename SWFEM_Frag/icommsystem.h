#pragma once

class ICommSystem {
public:
	virtual int getNodeId() const = 0;
	virtual int getNumOfNodes() const = 0;
};