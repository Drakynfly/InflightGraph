// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

/**
 *
 */
class INFLIGHTEDITOR_API FInflightGraphStyle
{
public:

	/** Styling for Inflight Graph Nodes */
	class FNode
	{
	public:
		static const FLinearColor Start;
		static const FLinearColor State;
		static const FLinearColor Input;
	};

	/** Styling for Inflight Graph Node Pins */
	class FPin
	{
	public:
		static const FLinearColor Default;
	};
};