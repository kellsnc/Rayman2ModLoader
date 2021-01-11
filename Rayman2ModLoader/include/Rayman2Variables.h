/*
 * Rayman2 Mod Loader
 * Rayman2 variables
 */

#ifndef RAYMAN2MODLOADER_VARS_H
#define RAYMAN2MODLOADER_VARS_H

typedef bool(__cdecl* BoolFuncPtr)(void);
typedef int(__cdecl* SectionInfoPtr)(tdstSectInfo_*, int);
typedef int(__cdecl* EvalFuncPtr)(HIE_tdstSuperObject*, tdstNodeInterpret_*, tdstGetSetParam_*);
typedef int(__cdecl* ProcedureFuncPtr)(HIE_tdstSuperObject*, tdstNodeInterpret_*);

DataPointer(float, aspectRatio, 0x49C498);
DataPointer(HWND, WindowHandle, 0x49F080);
DataArray(char, WindowName, 0x49F0A0, 8);
DataPointer(char, someModuleId, 0x49F14C);
DataPointer(int, bFirst, 0x49F2B4);
DataPointer(BoolFuncPtr, DrawFrame_Pointer, 0x49F37C);
DataArray(SectionInfoPtr, engineObjectFunctions, 0x49F4D8, 79);
DataPointer(char, g_ucGameModuleId, 0x49F630);
DataArray(char*, currentSlot, 0x49F8C0, 4);
DataPointer(char, GAM_g_ucSaveGameBeforeChangeLevel, 0x49F8D4);
DataPointer(int, g_ucGEOModuleId, 0x49FBBC);
DataPointer(char, g_ucGEOMMemMallocMode, 0x49FBC0);
DataPointer(float, GEO_g_xZFarTransparencyZone, 0x49FC04);
DataPointer(int, GLI_gs_lRequestedDisplayMode, 0x4A0484);
DataPointer(float, luminosity, 0x4A0488);
DataPointer(float, GLI_gsfWaterPlaneFogStart, 0x4A06F8);
DataPointer(int, OptionTexturesMem, 0x4A077C);
DataPointer(int, g_ucIPTModuleId, 0x4A0CFC);
DataPointer(int*, IPT_p_fn_bIsKeyWordValid, 0x4A0F18);
DataPointer(DNM_stMecObstacle*, g_a_stObstacle, 0x4A1164);
DataPointer(char, g_ucMmgModuleId, 0x4A11C4);
DataPointer(int, OptionParticuleRate, 0x4A1234);
DataPointer(char, g_ucRNDModuleId, 0x4A1F4C);
DataPointer(char*, g_a_stModuleBlocToSaveInLevel, 0x4A2028);
DataPointer(char*, g_a_stModuleBlocToSaveInFix, 0x4A2040);
DataPointer(char*, g_a_stModuleBlocToSaveInfos, 0x4A2068);
DataArray(char*, levels0Dat, 0x4A2090, 24);
DataPointer(char, g_ucSndModuleId, 0x4A22DC);
DataPointer(char, g_ucTMPModuleId, 0x4A3FD4);
DataPointer(char, g_ucVIGModuleId, 0x4A4024);
DataPointer(int, g_ulOverRideRayTraceSpoMask, 0x4A40E8);
DataPointer(char, g_ucAIModuleId, 0x4A417C);
DataArray(EvalFuncPtr, a_stTypeTable, 0x4A4180, 40);
DataPointer(ProcedureFuncPtr, a_stProcedureTable, 0x4A43E0);
DataPointer(char, cCanTestStatic, 0x4A544C);
DataPointer(EvalFuncPtr, a_stFunctionTable, 0x4A5460);
DataArray(BoolFuncPtr, _a_stKeyWordTable, 0x4A5E80, 6);
DataPointer(EvalFuncPtr, a_stConditionTable, 0x4A5EE0);
DataArray(BoolFuncPtr, a_stOperatorTable, 0x4A6398, 12);
DataPointer(char, gcSimulateRelease, 0x4A66BC);
DataPointer(char, importantSaveThing, 0x4A6798);
DataPointer(void*, COL_g_stCollisionCaseReal, 0x4A680C);
DataPointer(int, COL_g_lNbElementsInTable, 0x4A6810);
DataPointer(__int16*, COL_g_a12_stBoxEdges, 0x4A6882);
DataPointer(char, fileModule, 0x4A68EC);
DataPointer(int, COL_g_lMaxNumberOfCollisions, 0x4A6974);
DataPointer(int, g_hLoadedSuperObjectRoot, 0x4A6AC8);
DataPointer(char, g_bBeginMapSoundEventFlag, 0x4A6ACC);
DataPointer(int, pausedUpdateCounter, 0x4A6AE8);
DataPointer(int, g_stAlways, 0x4A6B18);
DataPointer(HIE_tdstSuperObject*, personalTypes_SO, 0x4A6B28);
DataPointer(int*, tdstStacks, 0x4A6B38);
DataPointer(int, g_bAnimConstantSpeed, 0x4A7060);
DataPointer(int, maxSlot, 0x4A7064);
DataPointer(char, gcGlobAleat, 0x4A7070);
DataPointer(int, g_bRealTimeAnimationLoad, 0x4A7104);
DataPointer(int, GEO_g_xZFar, 0x4A7204);
DataPointer(int, g_bGLDBlockSwaping, 0x4A7210);
DataPointer(Uint32, someBackgroundColor, 0x4A721C);
DataPointer(int, IsGLIInitialized, 0x4A7234);
DataPointer(int, hwnd, 0x4A7238);
DataPointer(char, GLI_cGlobalFogIsOn, 0x4A7248);
DataPointer(int, g_AlphabetCharacterpointer_new, 0x4A724C);
DataPointer(Uint32, GLI_g_hMenuBackgroundObject, 0x4A7250);
DataPointer(int, g_AlphabetCharacterPointer, 0x4A727C);
DataPointer(float, MEC_g_xBaseCoeff, 0x4B72C4);
DataPointer(float, MEC_g_xWalkCoeff, 0x4B72C8);
DataPointer(int, g_lCallCounter, 0x4B72CC);
DataPointer(char, g_bHighSpeed, 0x4B72D0);
DataPointer(int, SNA_g_stFixInfo, 0x4B72F0);
DataPointer(int, pointerCount, 0x4B7300);
DataPointer(int*, SNA_g_stFixInfo_0, 0x4B7304);
DataPointer(int, SNA_g_PTCRelocationTable, 0x4B7358);
DataPointer(char, g_ucMemDescSnapshot, 0x4B7464);
DataPointer(int, SNA_g_eFileCurrentlyOpened, 0x4B7468);
DataArray(char, GF_filename, 0x4B7500, 4096);
DataPointer(int, _HIE_g_lNbMatrixInStack, 0x4B98D4);
DataPointer(__int16, g_xFixIndex, 0x4B98DC);
DataArray(float, mainCharacterCoordinates, 0x4B99F8, 4);
DataPointer(__int16, VIG_g_hGLDDevice, 0x4B9AAC);
DataPointer(__int16, VIG_g_hGLDViewport, 0x4B9AB0);
DataPointer(int, VIG_g_hConcatVignetteFile, 0x4B9ABC);
DataPointer(float, globalSpriteTimer, 0x4B9AFC);
DataPointer(char, g_bInGameMenu, 0x4B9BC8);
DataPointer(int, g_bReInitAllDynamicActors, 0x4B9C10);
DataPointer(int, cameraTarget, 0x4B9C14);
DataPointer(char, ucIsInSchedule, 0x4B9C18);
DataPointer(char, g_ucIsInMacro, 0x4B9C1C);
DataPointer(tdstNodeInterpret_*, g_p_stTreeMacro, 0x4B9C20);
DataPointer(int, g_hCurrentSuperObjPerso, 0x4B9C28);
DataPointer(char, gcSimulateNotU64, 0x4B9C34);
DataPointer(char, breakTheMold, 0x4B9C38);
DataPointer(int, importantSaveThing2, 0x4B9C3C);
DataPointer(int, checkDWord, 0x4B9C40);
DataPointer(int, FIL_g_hHandleToFileInConcatFile, 0x4B9C48);
DataArray(char, cmdline, 0x4E0DA0, MAX_PATH);
DataPointer(HANDLE, hSemaphore_0, 0x4E0D80);
DataPointer(HANDLE, ExitEvt, 0x4E0ECC);
DataArray(__byte, textTable, 0x4E1093, 420);
DataPointer(char, cNoDynChangeTheta, 0x4E92FC);
DataPointer(char, cRefAxisIsAlreadyComputed, 0x4E92FD);
DataPointer(int*, g_a_hPersoInZone, 0x4E9320);
DataPointer(char, g_ucUseDefaultActionReturn, 0x4E9398);
DataPointer(char, g_ucNewActionReturn, 0x4E9399);
DataPointer(char, g_ucNRule, 0x4E939A);
DataPointer(char, bSomethingDone, 0x4E939B);
DataPointer(tdstIntelligence_*, g_p_stIntelligence, 0x4E939C);
DataPointer(char, checkByte, 0x4F6F68);
DataPointer(int, COL_g_d_lTaggedFacesTable, 0x4FAABC);
DataPointer(int*, g_stErmTheLastErrorInfo, 0x4FB620);
DataPointer(int, gs_hFirstSubMapPosition, 0x4FF760);
DataPointer(int, g_hCharacterLauchingSoundEvents, 0x4FF764);
DataPointer(int, g_stIndexMicrosList, 0x4FF770);
DataPointer(int, g_Randomhandle, 0x4FF77C);
DataPointer(int, PLA_g_ulMaxOccupationOfSupObjHeap, 0x4FF780);
DataPointer(int, PLA_g_ulMaxOccupationOfChannels, 0x4FF784);
DataPointer(int, g_lSoundObjectTypeMusic, 0x4FF788);
DataPointer(int, g_lSoundObjectTypeAnim, 0x4FF7D0);
DataPointer(int, FON_g_stGeneral, 0x500260);
DataPointer(int, textPointer, 0x500270);
DataPointer(int, p_stFramesKF, 0x500274);
DataPointer(int, p_stA3dGENERAL, 0x500278);
DataPointer(int, p_stChannels, 0x50027C);
DataPointer(int, p_stFrames, 0x500280);
DataPointer(int, p_stHierarchies, 0x500284);
DataPointer(int, p_stMorphData, 0x500288);
DataPointer(int, p_stKeyFrames, 0x50028C);
DataPointer(int, p_stOnlyFrames, 0x500290);
DataPointer(int, p_a3_xVectors, 0x500294);
DataPointer(int, p_stEvents, 0x500298);
DataPointer(int, p_stNTT0, 0x50029C);
DataPointer(int, p_a4_xQuaternions, 0x5002A0);
DataPointer(int, g_st_3DOS_EntryActions, 0x5002C0);
DataPointer(int, g_hCollisionGeoObj, 0x50036C);
DataPointer(char, _g_ucIsEdInGhostMode, 0x500370);
DataPointer(char, g_cIsLevel0k, 0x500371);
DataPointer(int, gp_stLight, 0x500374);
DataPointer(EngineStructure, g_stEngineStructure, 0x500380);
DataPointer(int, theCamera, 0x500554);
DataPointer(HIE_tdstSuperObject*, mainChar, 0x500578);
DataPointer(char, engineFrozen, 0x500FAA);
DataPointer(HIE_tdstSuperObject*, g_hSOCurrentMainSector, 0x500FB0);
DataPointer(int*, g_a_pfnDynamicFunction, 0x500FB8);
DataPointer(HIE_tdstSuperObject*, SECT_hFatherSector, 0x500FC0);
DataPointer(HIE_tdstSuperObject*, g_hSOPreviousMainSector, 0x500FC8);
DataPointer(HIE_tdstSuperObject*, gp_stDynamicWorld, 0x500FD0);
DataPointer(int, gp_stActualWorld, 0x5013C8);
DataPointer(int, g_stBeginMapSoundEvent, 0x5013CC);
DataPointer(int, g_hStaticCollisionGeoObj, 0x501404);
DataPointer(char, _GEO_g_bDynamicAllocation, 0x501524);
DataPointer(int, _GEO_g_stMyBlockInfo, 0x501530);
DataPointer(int*, g_GLI_iTexturesToCreate, 0x501644);
DataPointer(int*, gs_aDEFTableOfTextureMemoryChannels, 0x501660);
DataPointer(int, _GLI_BIG_GLOBALS, 0x5036AC);
DataPointer(char, colorRed, 0x503748);
DataPointer(char, colorGreen, 0x503749);
DataPointer(char, colorBlue, 0x50374A);
DataPointer(int*, lightArray, 0x503760);
DataPointer(char*, g_ucTableOfActiveLightsForChar, 0x503C20);
DataPointer(int, gs_CurrentNumberOfLightInViewport, 0x503D4C);
DataPointer(int, GLI_gsCurrentMemoryChannel, 0x503D54);
DataPointer(float, fogNear2, 0x503D64);
DataPointer(char, GLI_g_bSaveFog, 0x503D68);
DataPointer(float, fogNear1, 0x503D6C);
DataPointer(float, fogFar2, 0x503D70);
DataPointer(float, fogFar1, 0x503D74);
DataPointer(float, fogBlendMaybe, 0x503DA4);
DataPointer(int, fogColor, 0x504000);
DataPointer(int, xSinusEffectDepthStart, 0x50401C);
DataPointer(float, GLI_gsfWaterPlaneFogColor, 0x504070);
DataPointer(char, g_cSinusEffectFlag, 0x504088);
DataPointer(char, g_cSinusEffectState, 0x50409C);
DataPointer(int, fWaterPlaneDistance, 0x5040AC);
DataPointer(int, stWaterPlaneNormale, 0x5040B0);
DataPointer(float, stSinEffectAmp, 0x5040D0);
DataPointer(int, a3_lSinEffectFreq, 0x5042E0);
DataPointer(float, a3_xSinEffectBase, 0x5042F0);
DataPointer(char*, a3_xThreeModesArray, 0x504300);
DataPointer(int, GLI_gs_lCurrentDisplayMode, 0x504318);
DataPointer(int*, isFullscreen, 0x504320);
DataPointer(int*, width, 0x504324);
DataPointer(int*, height, 0x504328);
DataPointer(int*, bits, 0x50432C);
DataPointer(int, OptionScreenWidth, 0x5047FC);
DataPointer(int, OptionScreenHeight, 0x504800);
DataPointer(int, OptionScreenMode, 0x504804);
DataPointer(int, OptionScreenDepth, 0x504808);
DataPointer(int, OptionLanguage, 0x500FA8);
DataPointer(int, _g_p_stCurrentMatrix, 0x506B00);
DataPointer(int, IPT_g_hNextParameter, 0x509E38);
DataPointer(int, IPT_g_ulSequenceAnalyseNumber, 0x509E3C);
DataPointer(int, IPT_g_bAtLeastOneActionIsValidated, 0x509E40);
DataPointer(char, IPT_g_hInputStructure, 0x509E60);
DataPointer(int, fileHandle_, 0x509E61);
DataPointer(int, buff__, 0x509E65);
DataPointer(int, entryElementList, 0x50A564);
DataPointer(struct_DnmReport, g_stReport, 0x50A9A0);
DataPointer(__int16, MGT_g_xMaxIndexOfActivatedMagnet, 0x50AC90);
DataPointer(__int16, MGT_g_xMaxIndexOfModifiedObject, 0x50AC92);
DataPointer(int*, MGT_g_aDEF_hActivatedMagnets, 0x50ACA0);
DataPointer(HGLOBAL, _g_a_p_stMmgModuleBlocksInfo, 0x50ACC0);
DataPointer(HGLOBAL, g_d_stCurrentModeInfo, 0x50B1E8);
DataPointer(int, POS_g_p_stIdentityMatrix, 0x510BA0);
DataPointer(int, fixFileObject, 0x5113EC);
DataPointer(int, size, 0x5114E0);
DataPointer(int, RND_thing, 0x5115AC);
DataPointer(int, RND_g_stRandomStructure, 0x5115B8);
DataPointer(int, SAI_g_stInternalStructure, 0x5115C0);
DataPointer(int, g_hShadowPolygonVisualMaterial, 0x5115CC);
DataPointer(__int16, g_xIndexOfShadow_maybe, 0x5115D0);
DataPointer(int, g_hShadowPolygonGameMaterial, 0x5115D4);
DataPointer(int, g_hShadowPolygonGameMaterialInit, 0x5116A0);
DataPointer(int, g_p_stTextureOfTextureShadow, 0x5116A4);
DataPointer(HANDLE, g_stDscFile, 0x5116C0);
DataPointer(char, g_ucMemorySnapshot, 0x5116EC);
DataPointer(void*, SNA_g_ucNextRelocationTableToLoad, 0x5116F0);
DataPointer(int*, _SNA_g_a_dwProtectKeyRelocationTableLoaded, 0x5116FC);
DataPointer(int*, SNA_g_a_dwProtectKeyRelocationTableLoaded, 0x511700);
DataPointer(int, levels0DatValue_1, 0x511750);
DataPointer(int, levels0DatValue_4, 0x511754);
DataPointer(int*, SNA_g_a_dwInitKeyRelocationTableLoaded, 0x511760);
DataPointer(int, levels0DatValue_0, 0x5117B0);
DataPointer(int, levels0DatValue_2, 0x5117B4);
DataPointer(int, gl_ulChecksum, 0x5117B8);
DataPointer(int, levels0DatValue_5, 0x5117BC);
DataPointer(int, levels0DatValue_3, 0x5117C0);
DataPointer(int, SNA_g_dwNumberOfRelocationTableLoaded, 0x5117C4);
DataPointer(char*, g_shouldRelocatePointer, 0x5117E0);
DataPointer(char, g_bSaveLoadFix, 0x5121D6);
DataPointer(int*, g_relocationTable, 0x5121E0);
DataPointer(FILE*, curOpenFile, 0x5149B8);
DataPointer(HANDLE, curOpenFileHandle2, 0x5149BC);
DataPointer(int, g_p_stAfterLastPtrRelocInfo, 0x5149C0);
DataPointer(struct_g_p_stNextPtrRelocInfo*, g_p_stNextPtrRelocInfo, 0x5149C4);
DataPointer(int, _g_p_stCurrentInCamCoordsMatrix, 0x514D64);
DataPointer(int*, gd_hFixSPO, 0x514E20);
DataPointer(int, updateCounter, 0x514EA0);
DataPointer(int, HIE_g_lNbMatrixInCameraStack, 0x51606C);
DataPointer(int*, fixGPTData, 0x516080);
DataPointer(char, gptSize, 0x516148);
DataPointer(char, VIG_g_stActualVignette, 0x5163E0);
DataPointer(char, VIG_g_bExtendedVignettesEnabled, 0x5166C0);
DataPointer(void*, modelPointer, 0x252B700);
DataPointer(void*, currentFace, 0x1000B6F4);

#endif