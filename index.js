const constants = require('./constants');
const spiCaller = require('./build/Release/spiCaller.node');

const parseAction = (action) => {
  const actionConst = constants.actions.get(action);
  if (typeof actionConst === 'undefined') {
    throw new Error('Unrecognized action name.')
  }
  return parseInt(actionConst, 10);
}

const parseReturnType = (returnType) => {
  const returnTypeConst = constants.returnTypes.get(returnType);
  if (typeof returnTypeConst === 'undefined') {
    throw new Error('Unrecognized returnType.')
  }
  return returnTypeConst;
}

const spiCallerWrapper = {
  spiGet(action, returnType) {
    return spiCaller.spiGet(parseAction(action), parseReturnType(returnType));
  },
  spiSet(action, value) {
    return spiCaller.spiSet(parseAction(action), value);
  }
}

module.exports = spiCallerWrapper;
