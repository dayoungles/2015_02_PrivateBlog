var express = require('express');
var router = express.Router();
var mongoose = require('mongoose');
var model = require('../model/models.js');
var path = require('path');
var sess;
var url = 'mongodb://localhost:27017/blog';


router.get('/login', function (req, res, next) {
	res.sendFile(path.join(__dirname + '/../public/login.html'));
});


router.post('/loginProcess', function (req, res, next) {
		sess = req.session;
		var user = model.users.findOne({
			email: req.body.email
		}, function (err, data) {

			if (err) return handleError(err);
			//if(data === null) {
			//	res.cookie('userName', "ghost");
			//	res.redirect('/index/1');
			//	return;
			//}
			if (data.password === req.body.password){
				sess.user =  data;
				console.log(data);
				res.redirect('/index/1');

			} else {
				res.send('password is incorrect');
			}
		})


});

router.get('/authFail', function(req, res){
	res.sendFile(path.join(__dirname + '/../public/authFail.html'));
});

router.get('/notMem', function(req, res){
	sess = req.session;
	sess.ghost= "ghost";
	res.redirect('/index/1');
});

router.get('/checkSession', function(req, res){
	sess = req.session;
	console.log('session: %s' , sess.id);
});

router.get('/logout', function(req, res){
	console.log('logout?');
	req.session.destroy(function(err){
		res.redirect("/users/login");
	});
})

module.exports = router;
