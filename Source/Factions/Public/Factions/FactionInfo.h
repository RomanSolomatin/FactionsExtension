// Copyright 2015-2018 Piperift. All Rights Reserved.

#pragma once

#include "GenericTeamAgentInterface.h"

#include "Faction.h"
#include "FactionInfo.generated.h"

class UFactionsSettings;

/**
 * Defines a relation between factions
*/
USTRUCT(BlueprintType)
struct FACTIONS_API FFactionRelation
{
    GENERATED_USTRUCT_BODY()
    
    FFactionRelation() : 
        FactionA(FFaction::NoFaction), FactionB(FFaction::NoFaction), Attitude(ETeamAttitude::Neutral)
    {}

    FFactionRelation(FFaction A, FFaction B, ETeamAttitude::Type InAttitude = ETeamAttitude::Neutral) :
        FactionA(A), FactionB(B), Attitude(InAttitude)
    {}

	/** First Faction of the relation */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "A"))
    FFaction FactionA;

	/** Second Faction of the relation */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "B"))
    FFaction FactionB;

	/** Defines how this two factions will react to each other */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TEnumAsByte<ETeamAttitude::Type> Attitude;


    bool IsValid() const
    {
        return !FactionA.IsNone() && !FactionB.IsNone();
    }

    FORCEINLINE bool operator==(const FFactionRelation& Other) const {
        return (FactionA == Other.FactionA && FactionB == Other.FactionB) ||
               (FactionA == Other.FactionB && FactionB == Other.FactionA);
    }
    FORCEINLINE bool operator!=(const FFactionRelation& Other) const { return !(*this == Other); }
    
    friend uint32 GetTypeHash(const FFactionRelation& InRelation)
    {
        return GetTypeHash(InRelation.FactionA) ^ GetTypeHash(InRelation.FactionB);
    }
};

/**
 * Struct containing information about a faction. Static use.
 */
USTRUCT(BlueprintType)
struct FACTIONS_API FFactionInfo
{
    GENERATED_USTRUCT_BODY()

public:
    FFactionInfo()
		: Name(NO_FACTION_NAME)
		, Color(FColor::Cyan)
		, AttitudeTowardsItself(ETeamAttitude::Friendly)
		, DefaultAttitudeTowardsOthers(ETeamAttitude::Neutral)
    {}

    FFactionInfo(FName InName, FLinearColor InColor = FColor::Cyan)
		: Name(InName)
		, Color(InColor)
		, AttitudeTowardsItself(ETeamAttitude::Friendly)
		, DefaultAttitudeTowardsOthers(ETeamAttitude::Neutral)
    {}

	/** Name of the faction */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Faction)
    FName Name;

	/** Color of the Faction. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Faction)
	FLinearColor Color;

	/** Attitude this faction will have against itself. Relations will override it. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Faction)
	TEnumAsByte<ETeamAttitude::Type> AttitudeTowardsItself;

	/** Attitude this faction will have against others. Relations will override it. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Faction)
	TEnumAsByte<ETeamAttitude::Type> DefaultAttitudeTowardsOthers;


    const FFaction GetFaction();

    void SetRelation(const FFaction& OtherFaction, const ETeamAttitude::Type Attitude);
};
