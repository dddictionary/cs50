import anime from "./node_modules/animejs/lib/anime.es.js"


let animation = anime({
    targets: 'div.welcome',
    translateX: 100,
    borderRadius: 50,
    duration: 1000,
    easing: 'linear',
    direction: 'alternate'
  });