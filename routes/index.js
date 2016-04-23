var express = require('express');
var router = express.Router();
var mongoose = require('mongoose');
var model = require('../model/models.js');
var path = require('path');
var sess;
var url = 'mongodb://localhost:27017/blog';

/* GET home page. */
router.get('/:page', function (req, res, next) {
    var pageNum = req.params.page;
    sess = req.session;
    var userName;
    if (sess.ghost) {
        userName = "notMem";
    } else {
        userName = sess.user.name;
    }
    console.log("auth : "+ req.session.user.auth);
    //model.posts.find({accessLevel: { $gte : req.session.auth}}, function (err, data) {
    model.posts.find(function (err, data) {
        res.render('index1', {title: 'Express', posts: data, userName: userName});
        console.log("who : "+ data.accessLevel);
    }).sort({_id: -1}).limit(10);
    //(pageNum-1)*5 ~ pageNum*5 선택하도록. post 넘버를 안 매겨서 아직 못함.
});


module.exports = router;


router.get('/post/:id', function (req, res, next) {

});

