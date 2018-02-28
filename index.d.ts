// Type definitions for windows-spi@0.0.7
// Project: MouseSettings
// Definitions by: tszafr

export as namespace windowsSpi;

export = {
  spiGet,
  spiSet,
};

/**
 * Used to retrieve information from SystemParametersInfo
 * @param action SystemParametersInfo action name
 * @param returnType String specyfing the return type. Supported values: 'bool', 'int', 'array'
 */
declare function spiGet(action: string, returnType: string): Promise<any>;

/**
 * Used to change settings using SystemParametersInfo
 * @param action SystemParametersInfo action name
 * @param value The value you want to pass to SPI
 */
declare function spiSet(action: string, value: any): Promise<string>;