var config = require('./config.js')
var mqtt = require('mqtt')
var axios = require('axios')
var client  = mqtt.connect(config.mqtt.server ,{ username: config.mqtt.username, password: config.mqtt.password })
var playlist = require('./playlist.js')
const baseUrl = config.sonos.baseUrl + '/' + config.sonos.room + '/'
const CancelToken = axios.CancelToken;
var cancelToken = null
var lastPlayerState = null

console.log(playlist)

client.on('connect', function () {
  client.subscribe('musicubes/#', function (err) {
    if (err) {
      console.log(err)
    }
    console.log('Ready to receive a MusiCube')
  })
})
client.on('message', function (topic, message) {
  if (topic == 'musicubes/cube') {
    const uri = getMusiCube(message)
    if (!uri) return console.log('Unknown MusiCube: ' + message)
    requestSonosUri(uri)
  }
})

function getMusiCube(identifier) {
  if (identifier == '00:00:00:00') return 'pause'
  if (identifier in playlist) return playlist[identifier]

  return false
}

function requestSonosUri(uri) {
  console.log('Requesting: ' + uri)

  if (cancelToken) {
    cancelToken.cancel();
  }

  cancelToken = CancelToken.source();
  axios.get(baseUrl + uri,{
    cancelToken: cancelToken.token
  })
    .then(result => {
      console.log('Request confirmed: ' + uri)
    })
    .catch(e => {
      if (axios.isCancel(e)) {
        return console.log('Request canceled: ', uri);
      }
      console.log(uri + ' is not a valid endpoint.')
    })
}

function getPlayerState() {
  const uri = baseUrl + 'state';
  axios.get(uri)
    .then(result => {
      if (result.data.playbackState && lastPlayerState != result.data.playbackState) {
        client.publish('musicubes/state', result.data.playbackState, {retain: true})
        lastPlayerState = result.data.playbackState
      }
      setTimeout(getPlayerState, 2000)
    })
    .catch(e => {
      console.log('Could not fetch player state. Retry in 5 seconds.');
      setTimeout(getPlayerState, 1000)
    })
}
getPlayerState();