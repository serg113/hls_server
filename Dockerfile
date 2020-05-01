FROM syons/ucv:1.0

WORKDIR /usr/src/app

EXPOSE 7070

ADD .  .

CMD [ "sh", "build_and_run"]