
#include <stdio.h>
#include "Fap.h"
#include "FapCrunch.h"

Fap FapConfig::instantiate() {
	return Fap(*this);
}

FapResult Fap::handle() {
	YmData ymData;

	if (!ymData.LoadFile(config.srcFile))
	{
		return FapResult(FapResultCode::CannotLoadInputFile);
	}

	ymData.Optimize();
	uint8_t nrRegistersToPlay = ymData.CountAndLimitRegChanges(config.threshold);
 
	FapData fapData(ymData);

	std::string content;

	// TODO store data instead of strings to ease reuse
	content += "\nSummary:\n";
	content += "  - Max registers to program: "  + std::to_string(nrRegistersToPlay) + "\n";
	content += "  - Constant Register 12: ";
	if (ymData.R12IsConst()) {content += "YES";} else { content += "NO... Damn your musician!";}
	content += "\n";

	bool success = fapData.WriteFile(config.dstFile, ymData, nrRegistersToPlay);

	if (!success) {
		return FapResult{FapResultCode::UnknownError, FapPayload{content}};
	}



	// TODO store data instead of strings to ease reuse
	if (ymData.R12IsConst())
	{
		int exeTime[] = { 592, 616, 640, 664 };
		content += "  - Play time: "+ std::to_string( exeTime[nrRegistersToPlay - 11]) +  "  NOPS\n";
		content += "  - Decrunch buffer size: 3144 (#B42)\n";
	}
	else
	{
		int exeTime[] = { 660, 684, 708, 732 };

		content += "  - Play time: " + std::to_string(exeTime[nrRegistersToPlay - 11]) + " NOPS\n";
		content += "  - Decrunch buffer size: 2888 (#C48)\n";
	}


	return FapResult{FapResultCode::Ok, FapPayload{content}};
}