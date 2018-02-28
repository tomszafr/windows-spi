const spiCaller = require('../build/Release/spiCaller.node');

const arg = {
  MouseSensitivity: 10,
  MouseSpeed: 2,
  MouseThreshold1: 2,
  MouseThreshold2: 5,
};

const test = async () => {
  const results = {};
  try {
    results.originalSensitivity = await spiCaller.spiGet(112, 1);
    results.originalSettings = await spiCaller.spiGet(3, 2);
    results.changeSensMessage = await spiCaller.spiSet(113, parseInt(arg.MouseSensitivity, 10));
    results.changeSettingsMessage = await spiCaller.spiSet(
      4,
      [
        parseInt(arg.MouseThreshold1, 10),
        parseInt(arg.MouseThreshold2, 10),
        parseInt(arg.MouseSpeed, 10)
      ]
    );
    results.changedSensitivity = await spiCaller.spiGet(112, 1);
    results.changedSettings = await spiCaller.spiGet(3, 2);
    results.resetSensMessage = await spiCaller.spiSet(
      113, parseInt(results.originalSensitivity, 10)
    );
    results.resetSettingsMessage = await spiCaller.spiSet(
      4, results.originalSettings
    );
  } catch (error) {
    console.error(error);
  }
  console.log(JSON.stringify(results, null, 4));
};

test();
